import argparse
from random import randint, sample
from tqdm import tqdm
import sys
from binary_tree import *

CASE_SEP = '**** ****'
MAX_ARG_STR_LEN = 99
EACH_ERROR_CASE = 3

shuffle_op = lambda x: sample(x, len(x))

def main(args: argparse.Namespace): 
    cases = []
    modes = args.modes
    assert set(modes) <= set(['preorder', 'postorder'])
    count = args.N
    p_bar = tqdm(total=args.N)
    while (count > 0):
        height = randint(args.min_height, args.max_height)
        root: BinaryNode = generate_random_binary_tree(height, (1, 99), allow_dup=not args.no_error)
        str_tree = stringify_binary_tree(root)
        in_order_list = traverse_binary_tree(root, 'inorder').split()
        in_order = ','.join(in_order_list)
        if len(in_order) > MAX_ARG_STR_LEN:
            continue
        for mode in modes: 
            try_ = 0
            trav = traverse_binary_tree(root, mode).split()
            if len(trav) > MAX_ARG_STR_LEN: 
                continue
            if args.force_error: 
                this_cases = []
                i = 0
                while (count > 0) and (i < EACH_ERROR_CASE) and (try_ < 50):
                    in_order_shuffle = shuffle_op(in_order_list)
                    try: 
                        _ = reconstruct_from_traversal(in_order_shuffle, trav, mode)
                        try_ += 1
                    except ValueError:
                        i += 1
                        count -= 1
                        p_bar.update(1)
                        this_cases.append((f'[{",".join(in_order_shuffle)}] [{",".join(trav)}] {mode}', 'error'))
                while (count > 0) and (i < 2 * EACH_ERROR_CASE) and (try_ < 50):
                    trav_shuffle = shuffle_op(trav)
                    try: 
                        _ = reconstruct_from_traversal(in_order_list, trav_shuffle, mode)
                        try_ += 1
                    except ValueError:
                        i += 1
                        count -= 1
                        p_bar.update(1)
                        this_cases.append((f'[{in_order}] [{",".join(trav_shuffle)}] {mode}', 'error'))
                while (count > 0) and (i < 3 * EACH_ERROR_CASE) and (try_ < 50):
                    in_order_shuffle = shuffle_op(in_order_list)
                    trav_shuffle = shuffle_op(trav)
                    try: 
                        _ = reconstruct_from_traversal(in_order_shuffle, trav_shuffle, mode)
                        try_ += 1
                    except ValueError:
                        i += 1
                        count -= 1
                        p_bar.update(1)
                        this_cases.append((f'[{",".join(in_order_list)}] [{",".join(trav_shuffle)}] {mode}', 'error'))
                this_cases = list(set(this_cases))
                cases.extend(this_cases)
            else: 
                try: 
                    _ = reconstruct_from_traversal(in_order_list, trav, mode)
                    cases.append((f'[{in_order}] [{",".join(trav)}] {mode[:-5]}', str_tree))
                except ValueError: 
                    cases.append((f'[{",".join(in_order_list)}] [{",".join(trav)}] {mode[:-5]}', 'error'))
                count -= 1
                p_bar.update(1)
    print((f'\n{CASE_SEP}\n').join([f'{tup[0]}\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='Binary Tree Traversal')
    parser.add_argument('-N', type=int, required=True, help='The number of trees to generate')
    parser.add_argument('--min-height', '-m', type=int, required=True, help='The minimum height of the tree')
    parser.add_argument('--max-height', '-M', type=int, required=True, help='The maximum height of the tree')
    parser.add_argument('--modes', nargs='*', default=['preorder', 'postorder'], help='The traversal modes to use')
    parser.add_argument('--no-error', action='store_true', help='Do not generate error cases')
    parser.add_argument('--force-error', action='store_true', help='Make error cases')
    args = parser.parse_args()
    main(args)
