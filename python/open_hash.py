import argparse
from random import randint, choices, random

CASE_SEP = '**** ****'

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in range(args.N):
        length = randint(args.min_length, args.max_length)
        M = randint(args.min_M, args.max_M)
        instructions = [f"('M',{M})"]
        hash_table = [[] for _ in range(M)]
        for _ in range(length): 
            val = randint(1, 99999)
            instructions.append(f"('insertion',{val})")
            hash_table[val % M].append(val)

        hash_table_repr = {}
        for i, bucket in enumerate(hash_table):
            if len(bucket) == 0:
                hash_table_repr[i] = 'empty'
            else: 
                hash_table_repr[i] = ', '.join([str(elem) for elem in bucket])
        cases.append(
            (
                ', '.join(instructions), 
                '\n'.join([f'{key}: {val}' for key, val in sorted(hash_table_repr.items(), key=lambda x: x[0])])
            )
        )
    print((f'\n{CASE_SEP}\n').join([f'[{tup[0]}]\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='Test Case Gen for PA3 Task 5: Open Hash Table')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min-length', type=int, required=True, help='The minimum length of the instruction')
    parser.add_argument('--max-length', type=int, required=True, help='The maximum length of the instruction')
    parser.add_argument('--min-M', type=int, required=True, help='The minimum hash table size')
    parser.add_argument('--max-M', type=int, required=True, help='The maximum hash table size')
    args = parser.parse_args()
    main(args)
