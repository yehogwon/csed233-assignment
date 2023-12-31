import argparse
from random import randint
from tqdm import tqdm
from binary_tree import *

CASE_SEP = '**** ****'

def main(args: argparse.Namespace): 
    cases = []
    p_bar = tqdm(range(args.N))
    modes = args.modes
    for _ in p_bar:
        height = randint(args.min_height, args.max_height)
        p_bar.set_description(f'Generating a random binary tree of height {height}')
        root: BinaryNode = generate_random_binary_tree(height)
        str_tree: str = stringify_binary_tree(root)
        cases += [
            (f'{str_tree} {mode}', traverse_binary_tree(root, mode)) for mode in modes
        ]
    print((f'\n{CASE_SEP}\n').join([f'{tup[0]}\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='Binary Tree Traversal')
    parser.add_argument('-N', type=int, required=True, help='The number of trees to generate')
    parser.add_argument('--min-height', '-m', type=int, required=True, help='The minimum height of the tree')
    parser.add_argument('--max-height', '-M', type=int, required=True, help='The maximum height of the tree')
    parser.add_argument('--modes', nargs='*', default=['preorder', 'inorder', 'postorder', 'levelorder'], help='The traversal modes to use')
    args = parser.parse_args()
    main(args)
