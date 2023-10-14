from queue import PriorityQueue
import argparse
from random import randint, choices

CASE_SEP = '**** ****'
MAX_SIZE = 100

COMMANDS = ['insert', 'isEmpty', 'getMax']
COMMANDS_RM = ['insert', 'isEmpty', 'removeMax']
COMMANDS_WEIGHTS = [0.42, 0.2, 0.38]

def main(args: argparse.Namespace) -> None: 
    commands = COMMANDS_RM if args.support_remove else COMMANDS
    cases = []
    for _ in range(args.N) :
        length = randint(args.min_length, args.max_length)
        case = []
        outputs = []
        pq = PriorityQueue(MAX_SIZE)
        error = False
        for command in choices(commands, COMMANDS_WEIGHTS, k=length):
            value = randint(0, 100) if command == 'insert' else 0
            case.append(f'(\'{command}\', {value})')
            if command == 'insert':
                if pq.full(): 
                    outputs.append('Error')
                    error = True
                    break
                pq.put((-value, value)) # Max Heap; reveerse the original priority scheme
            elif command == 'isEmpty':
                outputs.append(str(pq.empty()))
            elif command == 'getMax':
                if pq.empty():
                    outputs.append('Empty')
                else: 
                    outputs.append(str(pq.queue[0][1]))
            elif command == 'removeMax':
                if pq.empty():
                    outputs.append('Empty')
                else: 
                    pq.get()
        if not error: 
            outputs.append(' '.join([str(tup[1]) for tup in pq.queue]))
        cases.append(('[' + ', '.join(case) + ']', ' '.join(outputs)))
    print((f'\n{CASE_SEP}\n').join([f'{tup[0]}\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='Priority queue')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min-length', '-m', type=int, required=True, help='The minimum length of the instruction')
    parser.add_argument('--max-length', '-M', type=int, required=True, help='The maximum length of the instruction')
    parser.add_argument('--support-remove', '-r', action='store_true', help='Whether to support removeMax')
    args = parser.parse_args()
    main(args)
