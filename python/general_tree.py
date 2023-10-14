from typing import TypeVar, Generic, Optional, List
import argparse
from random import randint
from binary_tree import *

T = TypeVar('T')
class Node(Generic[T]): 
    def __init__(self, value: Optional[T]=None, left: Optional['Node[T]']=None, right: Optional['Node[T]']=None) -> None:
        self.value: Optional[T] = value
        self.children: List[Node[T]] = []
    
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

def left_child_right_sibling(root: Node) -> BinaryNode: 
    if not root: 
        return None
    if not root.left: 
        return root
    left_child_right_sibling(root.left).right = root.right
    root.right = None
    return left_child_right_sibling(root.left)

def binary_tree_to_general_tree(root: BinaryNode) -> Node:
    if not root: 
        return None
    node = Node(root.value)
    if root.left: 
        node.add_child(binary_tree_to_general_tree(root.left))
    if root.right: 
        node.add_child(binary_tree_to_general_tree(root.right))
    return node

def main(args: argparse.Namespace) -> None: 
    trees = []
    for _ in range(args.N):
        pass
    print('\n'.join([f'{tup[0]}\n{tup[1]}' for tup in trees]))

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='General Tree')
    parser.add_argument('--N', type=int, default=10, help='Number of trees to generate')
    parser.add_argument('--min-height', '-m', type=int, default=1, help='Minimum height of the tree')
    parser.add_argument('--max-height', '-M', type=int, default=10, help='Maximum height of the tree')
    args = parser.parse_args()
    main(args)
