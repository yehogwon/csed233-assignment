from typing import TypeVar, Generic, Optional, List
import argparse
from random import choices, randint, random

CASE_SEP = '**** ****'

T = TypeVar('T')
class BSTNode(Generic[T]): 
    def __init__(self, key: T, left: Optional['BSTNode[T]']=None, right: Optional['BSTNode[T]']=None) -> None:
        self.key: T = key
        self.left: Optional[BSTNode[T]] = left
        self.right: Optional[BSTNode[T]] = right
    
    def __eq__(self, other: 'BSTNode[T]') -> bool:
        if not isinstance(other, BSTNode): 
            return False
        return self.key == other.key

class BST(Generic[T]): 
    def __init__(self) -> None:
        super().__init__()
        self.root = None
        self.n_nodes = 0

    def insert(self, key: T) -> bool: 
        if not self.root: 
            self.root = BSTNode(key)
        else: 
            cur_ = self.root
            while cur_: 
                if key < cur_.key: 
                    if cur_.left: 
                        cur_ = cur_.left
                    else: 
                        cur_.left = BSTNode(key)
                        break
                elif key > cur_.key: 
                    if cur_.right: 
                        cur_ = cur_.right
                    else: 
                        cur_.right = BSTNode(key)
                        break
                else: 
                    return False
        self.n_nodes += 1
        return True

    def delete(self, value: T) -> bool: 
        if not self.root: 
            return False
        cur_ = self.root
        parent_ = None
        while cur_: 
            if value < cur_.key: 
                parent_ = cur_
                cur_ = cur_.left
            elif value > cur_.key: 
                parent_ = cur_
                cur_ = cur_.right
            else: 
                break
        
        if not cur_:
            return False
        
        if cur_.left and cur_.right: # deg 2
            succ_ = cur_.right
            succ_parent_ = cur_
            while succ_.left: 
                succ_parent_ = succ_
                succ_ = succ_.left
            cur_.key = succ_.key
            if succ_parent_.left == succ_: 
                succ_parent_.left = succ_.right
            else: 
                succ_parent_.right = succ_.right
        elif cur_.left: # deg 1 on left
            if parent_ is None: 
                self.root = cur_.left
            elif parent_.left == cur_:
                parent_.left = cur_.left
            else:
                parent_.right = cur_.left
        elif cur_.right: # deg 1 on right
            if parent_ is None: 
                self.root = cur_.right
            elif parent_.left == cur_:
                parent_.left = cur_.right
            else:
                parent_.right = cur_.right
        else: # deg 0
            if parent_ is None: 
                self.root = None
            elif parent_.left == cur_:
                parent_.left = None
            else:
                parent_.right = None
        self.n_nodes -= 1
        return True
    
    def __len__(self) -> int: 
        return self.n_nodes

def nth_smallest(bst: BST[T], n: int) -> Optional[T]:
    if n > len(bst): 
        return None
    in_ = inorder(bst)
    return in_[n - 1]

def _preorder(bst_node: BSTNode[T]) -> List[T]: 
    if not bst_node:
        return []
    return [bst_node.key] + _preorder(bst_node.left) + _preorder(bst_node.right)

def preorder(bst: BST[T]) -> List[T]:
    return _preorder(bst.root)

def _inorder(bst_node: BSTNode[T]) -> List[T]:
    if not bst_node:
        return []
    return _inorder(bst_node.left) + [bst_node.key] + _inorder(bst_node.right)

def inorder(bst: BST[T]) -> List[T]:
    return _inorder(bst.root)

INSTRUCTION_PROB = {
    'insertion': 0.45, 
    'deletion': 0.35, 
    'findNthMinimum': 0.2
}

def gen_instruction(): 
    return choices(
        population=list(INSTRUCTION_PROB.keys()), 
        weights=list(INSTRUCTION_PROB.values()), 
        k=1
    )[0]

def main(args: argparse.Namespace) -> None: 
    cases = []
    for _ in range(args.N): 
        bst = BST()
        instructions = []
        inserted_values = []
        outputs = []
        for _ in range(randint(args.min, args.max)): 
            instruction = gen_instruction()
            value = randint(1, 99)
            if instruction == 'insertion': 
                if bst.insert(value): 
                    inserted_values.append(value)
                    outputs.append(0)
                else:
                    outputs.append(-1)
            elif instruction == 'deletion':
                if len(inserted_values) > 0 and random() < 0.5: 
                    value = choices(inserted_values, k=1)[0]
                if bst.delete(value): 
                    outputs.append(0)
                else: 
                    outputs.append(-1)
            else:
                value = randint(0, int(len(bst) * 1.5)) + 1
                nth_min = nth_smallest(bst, value)
                if nth_min is None: 
                    outputs.append(-1)
                else:
                    outputs.append(nth_min)
            instructions.append(f"('{instruction}', {value})")
        pre_ = [str(x) for x in preorder(bst)]
        in_ = [str(x) for x in inorder(bst)]
        if len(pre_) > 0: 
            outputs.append(' '.join(pre_))
        if len(in_) > 0:
            outputs.append(' '.join(in_))
        cases.append(
            (
                ','.join(instructions), 
                '\n'.join([str(elem) for elem in outputs])
            )
        )
    
    print((f'\n{CASE_SEP}\n').join([f'[{tup[0]}]\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Binary Search Tree')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min', '-m', type=int, required=True, help='The minimum length of instruction')
    parser.add_argument('--max', '-M', type=int, required=True, help='The maximum length of instruction')
    args = parser.parse_args()
    main(args)