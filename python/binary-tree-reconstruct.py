import importlib
BT = importlib.import_module('binary-tree')
globals().update({k: getattr(BT, k) for k in BT.__all__}) # from binary-tree import *

import argparse
from random import randint
from tqdm import tqdm

CASE_SEP = '**** ****'
MAX_ARG_STR_LEN = 99

def main(args: argparse.Namespace): 
    cases = []
    p_bar = tqdm(range(args.N))
    modes = args.modes
    assert set(modes) <= set(['preorder', 'postorder'])
    for _ in p_bar:
        height = randint(args.min_height, args.max_height)
        p_bar.set_description(f'Generating a random binary tree of height {height}')
        root: BinaryNode = generate_random_binary_tree(height, (1, 99), allow_dup=not args.no_error)
        str_tree = stringify_binary_tree(root)
        in_order_list = traverse_binary_tree(root, 'inorder').split()
        in_order = ','.join(in_order_list)
        if len(set(in_order_list)) != len(in_order_list): 
            output = 'error'
        else: 
            output = str_tree
        if len(in_order) > MAX_ARG_STR_LEN:
            continue
        for mode in modes: 
            trav = ','.join(traverse_binary_tree(root, mode).split())
            if len(trav) > MAX_ARG_STR_LEN: 
                continue
            cases.append((f'[{in_order}] [{trav}] {mode[:-5]}', output))
    print((f'\n{CASE_SEP}\n').join([f'{tup[0]}\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='Binary Tree Traversal')
    parser.add_argument('-N', type=int, required=True, help='The number of trees to generate')
    parser.add_argument('--min-height', '-m', type=int, required=True, help='The minimum height of the tree')
    parser.add_argument('--max-height', '-M', type=int, required=True, help='The maximum height of the tree')
    parser.add_argument('--modes', nargs='*', default=['preorder', 'postorder'], help='The traversal modes to use')
    parser.add_argument('--no-error', action='store_true', help='Do not generate error cases')
    args = parser.parse_args()
    main(args)
