from typing import TypeVar, Generic, Optional, List
import argparse
from random import choices, randint, random

from binary_search_tree import *

CASE_SEP = '**** ****'

class AVLNode:
    def __init__(self, key):
        self.key = key
        self.height = 1
        self.left = None
        self.right = None

class AVLTree:
    def __init__(self):
        self.root = None
        self.status = "OK"

    def height(self, node):
        if not node:
            return 0
        return node.height

    def update_height(self, node):
        if not node:
            return 0
        node.height = 1 + max(self.height(node.left), self.height(node.right))

    def balance_factor(self, node):
        if not node:
            return 0
        return self.height(node.left) - self.height(node.right)

    def rotate_right(self, y):
        x = y.left
        T2 = x.right

        x.right = y
        y.left = T2

        self.update_height(y)
        self.update_height(x)

        return x

    def rotate_left(self, x):
        y = x.right
        T2 = y.left

        y.left = x
        x.right = T2

        self.update_height(x)
        self.update_height(y)

        return y

    def insert(self, root, key):
        if not root:
            self.status = "OK"
            return AVLNode(key)

        if key < root.key:
            root.left = self.insert(root.left, key)
        elif key > root.key:
            root.right = self.insert(root.right, key)
        else:
            # Duplicate keys not allowed
            self.status = "Fail"
            return root

        self.update_height(root)

        balance = self.balance_factor(root)

        # Left Left (LL) Case
        if balance > 1 and key < root.left.key:
            self.status = 'LL'
            return self.rotate_right(root)

        # Right Right (RR) Case
        if balance < -1 and key > root.right.key:
            self.status = 'RR'
            return self.rotate_left(root)

        # Left Right (LR) Case
        if balance > 1 and key > root.left.key:
            self.status = 'LR'
            root.left = self.rotate_left(root.left)
            return self.rotate_right(root)

        # Right Left (RL) Case
        if balance < -1 and key < root.right.key:
            self.status = 'RL'
            root.right = self.rotate_right(root.right)
            return self.rotate_left(root)

        return root

    def delete(self, root, key):
        if not root:
            self.status = "Fail"
            return root

        if key < root.key:
            root.left = self.delete(root.left, key)
        elif key > root.key:
            root.right = self.delete(root.right, key)
        else:
            # Node with only one child or no child
            if not root.left:
                return root.right
            elif not root.right:
                return root.left

            # Node with two children
            temp = self.get_min_value_node(root.right)
            root.key = temp.key
            root.right = self.delete(root.right, temp.key)

        if not root:
            return root

        self.update_height(root)

        balance = self.balance_factor(root)

        # Left Left (LL) Case
        if balance > 1 and self.balance_factor(root.left) >= 0:
            return self.rotate_right(root)

        # Right Right (RR) Case
        if balance < -1 and self.balance_factor(root.right) <= 0:
            return self.rotate_left(root)

        # Left Right (LR) Case
        if balance > 1 and self.balance_factor(root.left) < 0:
            root.left = self.rotate_left(root.left)
            return self.rotate_right(root)

        # Right Left (RL) Case
        if balance < -1 and self.balance_factor(root.right) > 0:
            root.right = self.rotate_right(root.right)
            return self.rotate_left(root)

        return root

    def get_min_value_node(self, node):
        current = node
        while current.left:
            current = current.left
        return current

    def insert_key(self, key):
        self.root = self.insert(self.root, key)
        return self.status

    def delete_key(self, key):
        self.status = "OK"
        self.root = self.delete(self.root, key)
        return self.status
    
    def preorder_helper(self, root):
        if not root:
            return []
        return [root.key] + self.preorder_helper(root.left) + self.preorder_helper(root.right)

    def preorder(self):
        return self.preorder_helper(self.root)
    
    def inorder_helper(self, root):
        if not root:
            return []
        return self.inorder_helper(root.left) + [root.key] + self.inorder_helper(root.right)
    
    def inorder(self):
        return self.inorder_helper(self.root)


INSTRUCTION_PROB = {
    'insertion': 0.7, 
    'deletion': 0.3, 
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
        avl = AVLTree()
        root = None
        instructions = []
        inserted_values = []
        outputs = []
        for _ in range(randint(args.min, args.max)): 
            instruction = gen_instruction()
            value = randint(1, 99)
            if instruction == 'insertion': 
                status = avl.insert_key(value)
                if status != 'Fail': 
                    inserted_values.append(value)
                outputs.append(status)
            elif instruction == 'deletion':
                if len(inserted_values) > 0 and random() < 0.5: 
                    value = choices(inserted_values, k=1)[0]
                status = avl.delete_key(value)
                if status != 'Fail': 
                    inserted_values.remove(value)
                outputs.append(status)
            instructions.append(f"('{instruction}', {value})")
        pre_ = [str(x) for x in avl.preorder()]
        in_ = [str(x) for x in avl.inorder()]
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