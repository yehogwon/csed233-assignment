import argparse
from random import randint, choices, random

commands = ['e', 'd', 'show', 'size', 'isEmpty', 'clear']
weights = [0.3, 0.2, 0.125, 0.125, 0.125, 0.125]

commands_no_d = ['e', 'show', 'size', 'isEmpty', 'clear']
weights_no_d = [0.4, 0.15, 0.15, 0.15, 0.15]

prob_error = 0.3

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in range(args.N):
        length = randint(args.min_length, args.max_length)
        case = []
        outputs = []
        cur_queue = []
        is_error = random() < prob_error
        for _ in range(length):
            if not is_error and cur_queue is not None and len(cur_queue) == 0: 
                candidates = commands_no_d
                cur_weights = weights_no_d
            else: 
                candidates = commands
                cur_weights = weights
            command = choices(candidates, cur_weights)[0]
            if command == 'e':
                val = randint(0, 100)
                case.append(f'(\'{command}\', {val})')
                if cur_queue is not None: 
                    cur_queue.append(val)
            elif command == 'show': 
                case.append(f'(\'{command}\', NULL)')
                if cur_queue is not None: 
                    if len(cur_queue) == 0: 
                        outputs.append('empty')
                    else: 
                        outputs += [str(x) for x in cur_queue]
            elif command == 'size': 
                case.append(f'(\'{command}\', NULL)')
                if cur_queue is not None: 
                    outputs.append(str(len(cur_queue)))
            elif command == 'isEmpty': 
                case.append(f'(\'{command}\', NULL)')
                if cur_queue is not None: 
                    outputs.append('T' if len(cur_queue) == 0 else 'F')
            elif command == 'clear': 
                case.append(f'(\'{command}\', NULL)')
                if cur_queue is not None:
                    cur_queue = []
            elif command == 'd': 
                case.append(f'(\'{command}\', NULL)')
                if cur_queue is None or len(cur_queue) == 0:
                    cur_queue = None
                else: 
                    cur_queue.pop(0)
        if cur_queue is not None:
            cases.append(('[' + ', '.join(case) + ']', ' '.join(outputs)))
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
