from typing import TypeVar, Generic, Optional, List, Tuple, Union, Callable
from random import randint, random, shuffle
import argparse

__all__ = [
    'BinaryNode', 
    'traverse_binary_tree', 
    'stringify_binary_tree',
    'generate_random_binary_tree', 
    'reconstruct_from_traversal'
]

T = TypeVar('T')
class BinaryNode(Generic[T]): 
    def __init__(self, value: Union[Optional[T], str]=None, left: Optional['BinaryNode[T]']=None, right: Optional['BinaryNode[T]']=None) -> None:
        if isinstance(value, str) and not left and not right: 
            _root = construct_from_string(value)
            self.value = _root.value
            self.left = _root.left
            self.right = _root.right
        else: 
            self.value: Optional[T] = value
            self.left: Optional[BinaryNode[T]] = left
            self.right: Optional[BinaryNode[T]] = right
    
    def num_children(self) -> int:
        return int(self.left is not None) + int(self.right is not None)
    
    def __eq__(self, other: 'BinaryNode[T]') -> bool:
        if not isinstance(other, BinaryNode): 
            return False
        return self.value == other.value and self.left == other.left and self.right == other.right

    def __repr__(self) -> str:
        return f'BinaryNode({self.value} -> # of children: {self.num_children()})'

def _split_binary_tree_format(s: str) -> Tuple[Optional[str]]: 
    if len(s) == 0: 
        return (None, None, None)
    value = 0
    start = -1
    for i, c in enumerate(s): 
        if c == '(': 
            start = i
            break
        else: 
            value = 10 * value + int(c)
    if start == -1: 
        return (value, None, None)
    n_opens = 1
    i = start + 1
    while n_opens > 0:
        if s[i] == '(':
            n_opens += 1
        elif s[i] == ')':
            n_opens -= 1
        i += 1
    left = s[start + 1:i - 1]
    right = s[i + 1:-1]
    return (value, left, right)
    
def construct_from_string(s: Optional[str]) -> BinaryNode: 
    r'''
    Format: root_value(left, right)
    The string is given so that the corresponding tree can be constructed recursively. 
    Assume that s has valid parentheses. 
    '''

    if s is None or len(s) == 0: 
        return None
    _value, _left_string, _right_string = _split_binary_tree_format(s)
    return BinaryNode(_value, construct_from_string(_left_string), construct_from_string(_right_string))

def _preorder_binary_tree(root: BinaryNode) -> str: 
    if root is None: 
        return ''
    return f'{root.value} {_preorder_binary_tree(root.left)} {_preorder_binary_tree(root.right)}'

def _inorder_binary_tree(root: BinaryNode) -> str:
    if root is None: 
        return ''
    return f'{_inorder_binary_tree(root.left)} {root.value} {_inorder_binary_tree(root.right)}'

def _postorder_binary_tree(root: BinaryNode) -> str:
    if root is None: 
        return ''
    return f'{_postorder_binary_tree(root.left)} {_postorder_binary_tree(root.right)} {root.value}'

def _levelorder_binary_tree(root: BinaryNode) -> str:
    if root is None: 
        return ''
    queue: List[BinaryNode] = [root]
    result = ''
    while len(queue) > 0: 
        node = queue.pop(0)
        if node is not None: 
            result += f'{node.value} '
            queue.append(node.left)
            queue.append(node.right)
    return result

def traverse_binary_tree(root: BinaryNode, mode: str) -> str: 
    assert mode in ['preorder', 'inorder', 'postorder', 'levelorder'], f'Invalid mode: {mode}'
    if mode == 'preorder':
        return _preorder_binary_tree(root)
    elif mode == 'inorder':
        return _inorder_binary_tree(root)
    elif mode == 'postorder':
        return _postorder_binary_tree(root)
    elif mode == 'levelorder':
        return _levelorder_binary_tree(root)

def stringify_binary_tree(root: BinaryNode) -> str: 
    r'''
    Convert the given binary tree into the recursive form: Root(LeftSubTree)(RightSubTree)
    '''
    if root is None: 
        return ''
    if not root.left and not root.right:
        return f'{root.value}'
    return f'{root.value}({stringify_binary_tree(root.left)})({stringify_binary_tree(root.right)})'

gen_prob = randint(30, 100) / 100
generate_prob = lambda: random() < gen_prob
candidates = []
def _generate_random_binary_tree(height: int, rand_val_gen: Callable, force: bool=False) -> BinaryNode:
    if height == 0: 
        return None
    if height == 1: 
        return BinaryNode(rand_val_gen()) if generate_prob() or force else None
    return BinaryNode(rand_val_gen(), _generate_random_binary_tree(height - 1, rand_val_gen), _generate_random_binary_tree(height - 1, rand_val_gen))

def generate_random_binary_tree(height: int, _range: Tuple[int, int]=(0, 9), allow_dup: bool=True) -> BinaryNode: 
    global candidates
    candidates = []
    if allow_dup: 
        rand_val_gen = lambda: randint(*_range)
    else: 
        candidates = list(range(*_range))
        if len(candidates) < 2 ** height: 
            candidates = list(range(1, 2 ** height + 10))
        shuffle(candidates)
        rand_val_gen = lambda: candidates.pop()

    return _generate_random_binary_tree(height, rand_val_gen=rand_val_gen, force=True)

T = TypeVar('T')
def reconstruct_from_traversal(inorder: list[T], traversal: list[T], mode: str) -> BinaryNode[T]: 
    r'''
    Reconstruct a binary tree from its inorder traversal and a traversal mode. 
    '''
    assert mode in ['preorder', 'postorder'], f'Invalid mode: {mode}'
    if len(inorder) != len(traversal) \
        or len(set(inorder)) != len(inorder) \
        or len(set(traversal)) != len(traversal):
        raise ValueError('Invalid tree traversal: the lengths of the traversals are not equal or there are duplicate values')
    if len(inorder) == 0: 
        return None
    root_value = traversal[0]
    try: 
        root_index = inorder.index(root_value)
    except ValueError:
        raise ValueError('Invalid tree traversal: the root index out of range')
    left_inorder = inorder[:root_index]
    right_inorder = inorder[root_index + 1:]
    left_traversal = traversal[1:len(left_inorder) + 1]
    right_traversal = traversal[len(left_inorder) + 1:]
    return BinaryNode(root_value, reconstruct_from_traversal(left_inorder, left_traversal, mode), reconstruct_from_traversal(right_inorder, right_traversal, mode))

def main(args: argparse.Namespace) -> None: 
    root = generate_random_binary_tree(args.height, (args.min, args.max), args.allow_dup)
    print('stringify:', stringify_binary_tree(root))
    print('preorder:', traverse_binary_tree(root, 'preorder'))
    print('inorder:', traverse_binary_tree(root, 'inorder'))
    print('postorder:', traverse_binary_tree(root, 'postorder'))
    print('levelorder:', traverse_binary_tree(root, 'levelorder'))

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='Binary Tree')
    parser.add_argument('--height', '-H', type=int, default=4, help='Height of the binary tree')
    parser.add_argument('--min', '-m', type=int, default=0, help='Minimum value of the binary tree')
    parser.add_argument('--max', '-M', type=int, default=9, help='Maximum value of the binary tree')
    parser.add_argument('--allow-dup', action='store_true', help='Allow duplicate values in the binary tree')
    args = parser.parse_args()
    # command example
    # > python binary-tree.py --height 4 --range 0 9 --allow-dup
    main(args)
