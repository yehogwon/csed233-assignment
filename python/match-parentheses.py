import argparse
from random import randint, choices

class Color:
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    DARKCYAN = '\033[36m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'

brackets_close_open_map = {
    '}': '{',
    ')': '(',
    ']': '['
}

tokens = list(brackets_close_open_map.keys() | brackets_close_open_map.values())

def isValid(s: str) -> bool:
    stack = []

    for c in s:
        if c in brackets_close_open_map.values():
            stack.append(c)
        else:
            if stack and brackets_close_open_map[c] == stack[-1]: 
                stack.pop()
            else: 
                return False
    return not stack

def main(args: argparse.Namespace) -> None:
    valids = []
    invalids = []

    while (len(valids) <= args.N or len(invalids) <= args.N): 
        length = randint(args.min_length, args.max_length)
        s = ''.join(choices(tokens, k=length))
        validity = isValid(s)
        if len(valids) <= args.N and validity:
            valids.append(s)
        elif len(invalids) <= args.N and not validity:
            invalids.append(s)

    print(Color.BOLD + Color.PURPLE + '[valid]\n' + Color.END, list(set(valids)))
    print(Color.BOLD + Color.PURPLE + '[invalid]\n' + Color.END, list(set(invalids)))

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description="Match parentheses")
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate for each valid and invalid')
    parser.add_argument('--min-length', '-m', type=int, required=True, help='The minimum length of the string')
    parser.add_argument('--max-length', '-M', type=int, required=True, help='The maximum length of the string')
    args = parser.parse_args()
    main(args)
