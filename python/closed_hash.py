import argparse
from random import randint, choices, random

CASE_SEP = '**** ****'

def digits_sum(n: int) -> int:
    return sum([int(digit) for digit in str(n)])

def h1(n: int, M: int) -> int:
    return digits_sum(n) % M

def h2(n: int, M: int) -> int:
    return 1 + (n % (M - 1))

def h(n: int, i: int, M: int) -> int:
    return (h1(n, M) + i * h2(n, M)) % M

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in range(args.N):
        length = randint(args.min_length, args.max_length)
        M = randint(args.min_M, args.max_M)
        instructions = [f"('M',{M})"]
        hash_table = [None] * M
        F = []
        for _ in range(length): 
            val = randint(1, 99999)
            instructions.append(f"('insertion',{val})")
            collision_cnt = 0
            while hash_table[h(val, collision_cnt, M)] is not None and collision_cnt < M: 
                collision_cnt += 1
            if collision_cnt == M: 
                F.append(val)
            else:
                hash_table[h(val, collision_cnt, M)] = val
        for i in range(len(hash_table)): 
            if hash_table[i] is None: 
                hash_table[i] = 'empty'
        output_pairs = [(index, value) for index, value in enumerate(hash_table)]
        output_pairs.append(('F', ', '.join([str(val) for val in F]) if len(F) > 0 else 'empty'))
        cases.append(
            (
                ', '.join(instructions), 
                '\n'.join([f'{pair[0]}: {pair[1]}' for pair in output_pairs])
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
