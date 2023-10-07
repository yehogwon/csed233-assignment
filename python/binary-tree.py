from typing import TypeVar, Generic, Optional, List, Tuple, Union, Callable
from random import randint, random, shuffle

__all__ = [
    'BinaryNode', 
    'traverse_binary_tree', 
    'stringify_binary_tree',
    'generate_random_binary_tree'
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

def _traverse_binary_tree(root: BinaryNode, mode: str) -> str: 
    assert mode in ['preorder', 'inorder', 'postorder', 'levelorder'], f'Invalid mode: {mode}'
    if root is None: 
        return ''
    if mode == 'preorder':
        return f'{root.value} {_traverse_binary_tree(root.left, mode)} {_traverse_binary_tree(root.right, mode)}'
    elif mode == 'inorder':
        return f'{_traverse_binary_tree(root.left, mode)} {root.value} {_traverse_binary_tree(root.right, mode)}'
    elif mode == 'postorder':
        return f'{_traverse_binary_tree(root.left, mode)} {_traverse_binary_tree(root.right, mode)} {root.value}'
    elif mode == 'levelorder':
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
    return ' '.join(_traverse_binary_tree(root, mode).strip().split())

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
    if len(inorder) == 0: 
        return None
    root_value = traversal[0]
    root_index = inorder.index(root_value)
    left_inorder = inorder[:root_index]
    right_inorder = inorder[root_index + 1:]
    left_traversal = traversal[1:len(left_inorder) + 1]
    right_traversal = traversal[len(left_inorder) + 1:]
    return BinaryNode(root_value, reconstruct_from_traversal(left_inorder, left_traversal, mode), reconstruct_from_traversal(right_inorder, right_traversal, mode))
