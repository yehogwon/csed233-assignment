from typing import TypeVar, Generic, Optional, List
import argparse
from random import randint, choices, random

CASE_SEP = '**** ****'

commands = ['e', 'd', 'show', 'size']
weights = [0.3, 0.2, 0.25, 0.25]

T = TypeVar('T')
class CircularQueue(Generic[T]):
    def __init__(self, max_size: int):
        self.max_size = max_size
        self.queue: List[Optional[T]] = [None] * max_size
        self.head = self.tail = -1
        self.size = 0

    def enqueue(self, data: T) -> None:
        if ((self.tail + 1) % self.max_size == self.head):
            return
        if (self.head == -1):
            self.head = 0
            self.tail = 0
            self.queue[self.tail] = data
        else:
            self.tail = (self.tail + 1) % self.max_size
            self.queue[self.tail] = data
        self.size += 1

    def dequeue(self) -> T: 
        if (self.head == -1):
            return
        elif (self.head == self.tail):
            temp = self.queue[self.head]
            self.head = -1
            self.tail = -1
        else:
            temp = self.queue[self.head]
            self.head = (self.head + 1) % self.max_size
        self.size -= 1
        return temp

    def __repr__(self) -> str:
        if (self.head == -1):
            return 'empty'
        show_ = ''
        if (self.tail >= self.head):
            for i in range(self.head, self.tail + 1):
                show_ += str(self.queue[i]) + ' '
        else:
            for i in range(self.head, self.max_size):
                show_ += str(self.queue[i]) + ' '
            for i in range(0, self.tail + 1):
                show_ += str(self.queue[i]) + ' '
        return show_
    
    def __len__(self) -> int: 
        return self.size

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in range(args.N):
        length = randint(args.min_length, args.max_length)
        case = []
        outputs = []
        queue = CircularQueue[int](randint(args.min_queue_max_length, args.max_queue_max_length))
        for _ in range(length):
            command = choices(commands, weights)[0]
            if command == 'e':
                val = randint(0, 100)
                case.append(f'(\'{command}\', {val})')
                queue.enqueue(val)
            elif command == 'd': 
                case.append(f'(\'{command}\', NULL)')
                queue.dequeue()
            elif command == 'show': 
                case.append(f'(\'{command}\', NULL)')
                outputs.append(str(queue))
            elif command == 'size': 
                case.append(f'(\'{command}\', NULL)')
                outputs.append(str(len(queue)) + ' ')
        cases.append(('[' + ', '.join(case) + ']', '\n'.join(outputs)))
    print((f'\n{CASE_SEP}\n').join([f'{tup[0]}\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description="Test Case Gen for PA1 Task 6: Circular Queue")
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min-queue-max-length', '-mM', type=int, required=True, help='The minimum value of the maximum length of the queue')
    parser.add_argument('--max-queue-max-length', '-MM', type=int, required=True, help='The maximum value of the maximum length of the queue')
    parser.add_argument('--min-length', '-m', type=int, required=True, help='The minimum length of the string')
    parser.add_argument('--max-length', '-M', type=int, required=True, help='The maximum length of the string')
    args = parser.parse_args()
    main(args)
