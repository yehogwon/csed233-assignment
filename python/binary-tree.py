from typing import TypeVar, Generic, Optional, List, Tuple

T = TypeVar('T')
class BinaryNode(Generic[T]): 
    def __init__(self, value: Optional[T]=None, left: Optional['BinaryNode[T]']=None, right: Optional['BinaryNode[T]']=None) -> None:
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

def _stringify_binary_tree(root: BinaryNode, mode: str) -> str: 
    assert mode in ['preorder', 'inorder', 'postorder', 'levelorder'], f'Invalid mode: {mode}'
    if root is None: 
        return ''
    if mode == 'preorder':
        return f'{root.value} {_stringify_binary_tree(root.left, mode)} {_stringify_binary_tree(root.right, mode)}'
    elif mode == 'inorder':
        return f'{_stringify_binary_tree(root.left, mode)} {root.value} {_stringify_binary_tree(root.right, mode)}'
    elif mode == 'postorder':
        return f'{_stringify_binary_tree(root.left, mode)} {_stringify_binary_tree(root.right, mode)} {root.value}'
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

def stringify_binary_tree(root: BinaryNode, mode: str) -> str: 
    return ' '.join(_stringify_binary_tree(root, mode).strip().split())
