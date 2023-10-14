from typing import TypeVar, Generic, Optional, List, Tuple
import argparse
from random import randint
import copy
from binary_tree import *

CASE_SEP = '**** ****'

T = TypeVar('T')
class Node(Generic[T]): 
    def __init__(self, value: Optional[T]=None, children: Optional[List['Node[T]']]=None) -> None:
        self.value: Optional[T] = value
        self.children: List[Node[T]] = [] if children is None else children.copy()
    
    def num_children(self) -> int:
        return len(self.children)
    
    def add_child(self, child: 'Node[T]') -> None:
        self.children.append(child)

    def preorder(self) -> str:
        ret = ''
        ret += f'{self.value} '
        for child in self.children: 
            ret += child.preorder()
        return ret
    
    def postorder(self) -> str:
        ret = ''
        for child in self.children: 
            ret += child.postorder()
        ret += f'{self.value} '
        return ret

    def __repr__(self) -> str:
        return f'Node({self.value} -> # of children: {self.num_children()})'

def stringify_tree(root: Node) -> str:
    if root is None: 
        return ''
    if root.num_children() == 0: 
        return f'{root.value}'
    if root.num_children() == 1:
        return f'{root.value}({stringify_tree(root.children[0])})'
    return f'{root.value}({")(".join([stringify_tree(child) for child in root.children])})'

def generate_random_tree(height: int, _range: Tuple[int, int]=(0, 9), _range_children: Tuple[int, int]=(0, 4)) -> Node: 
    if height == 0: 
        return None
    root = Node(randint(*_range))
    n_children = randint(*_range_children)
    if height == 1: 
        return root
    for _ in range(n_children):
        root.add_child(generate_random_tree(height - 1, _range))
    return root

def general_tree_to_lcrs(root: Optional[Node]) -> Optional[BinaryNode]: 
    if root is None: 
        return None
    lcrs_children = [k for child in root.children if (k := general_tree_to_lcrs(child)) is not None]
    if len(lcrs_children) == 0: 
        return BinaryNode(root.value)
    if len(lcrs_children) == 1:
        return BinaryNode(root.value, left=lcrs_children[0])
    for i in range(len(lcrs_children) - 1, 0, -1): 
        lcrs_children[i - 1].right = lcrs_children[i]
    return BinaryNode(root.value, left=lcrs_children[0])

def main(args: argparse.Namespace) -> None: 
    cases = []
    for _ in range(args.N):
        height = randint(args.min_height, args.max_height)
        general_root = generate_random_tree(height, _range=(0, 9), _range_children=(0, 5))
        binary_root = general_tree_to_lcrs(general_root)
        cases.append((stringify_binary_tree(binary_root), stringify_tree(general_root)))
    print((f'\n{CASE_SEP}\n').join([f'{tup[0]}\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='General Tree')
    parser.add_argument('-N', type=int, required=True, help='Number of trees to generate')
    parser.add_argument('--min-height', '-m', type=int, required=True, help='Minimum height of the tree')
    parser.add_argument('--max-height', '-M', type=int, required=True, help='Maximum height of the tree')
    args = parser.parse_args()
    main(args)
