import argparse
from random import randint, choices, random
from typing import List, Tuple

commands = ['insert', 'delete']
weights = [0.65, 0.35]
prob_error = 0.3

def main(args: argparse.Namespace) -> None:
    cases: List[Tuple[str, str]] = []
    for _ in range(args.N):
        length = randint(args.min_length, args.max_length)
        case = []
        cur_list = []
        is_error = random() < prob_error
        for _ in range(length):
            if not is_error and cur_list is not None and len(cur_list) == 0: 
                command = 'insert'
            else: 
                command = choices(commands, weights)[0]
            if command == 'insert':
                val = randint(0, 100)
                case.append(f'(\'{command}\', {val})')
                if cur_list is not None: 
                    cur_list.append(val)
            else:
                index = -1
                if not is_error and cur_list is not None and len(cur_list) > 0:
                    index = max(0, randint(0, len(cur_list) - 1))
                    cur_list.pop(index)
                else: 
                    index = randint(0, 100)
                    cur_list = None
                case.append(f'(\'{command}\', {index})')
            if cur_list is not None: 
                cur_list.sort()
        if cur_list is not None:
            cases.append(('[' + ', '.join(case) + ']', ' '.join(map(str, cur_list))))
        else:
            cases.append(('[' + ', '.join(case) + ']', 'error'))
    print('\n'.join([x for tup in cases for x in tup]))

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description="Test Case Gen for PA1 Task 3: Application of List")
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min-length', '-m', type=int, required=True, help='The minimum length of the string')
    parser.add_argument('--max-length', '-M', type=int, required=True, help='The maximum length of the string')
    args = parser.parse_args()
    main(args)
