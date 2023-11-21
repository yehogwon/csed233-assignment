import argparse
from random import randint, choices, random

CASE_SEP = '**** ****'

def insertion_sort(l: list) -> list[str]: 
    l = l.copy()
    process: list[str] = []
    process.append(' '.join([str(elem) for elem in l]))
    
    i = 1
    while i < len(l): 
        j = i
        no = True
        while j > 0 and l[j] < l[j - 1]: 
            no = False
            l[j], l[j - 1] = l[j - 1], l[j]
            j -= 1
        if not no: 
            process.append(' '.join([str(elem) for elem in l]))
        i += 1
    return process

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in range(args.N):
        length = randint(args.min_length, args.max_length)
        org = []
        for _ in range(length): 
            org.append(randint(1, 99))
        process_list = insertion_sort(org)

        inputs = [f"('insertion', {elem})" for elem in org]
        inputs.append("('insertionSort', NULL)")
        cases.append(
            (
                ','.join(inputs), 
                '\n'.join(process_list)
            )
        )
    print((f'\n{CASE_SEP}\n').join([f'[{tup[0]}]\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='Test Case Gen for PA3 Task 1: Insertion Sort')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min-length', '-m', type=int, required=True, help='The minimum length of the string')
    parser.add_argument('--max-length', '-M', type=int, required=True, help='The maximum length of the string')
    args = parser.parse_args()
    main(args)
