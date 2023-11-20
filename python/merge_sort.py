import argparse
from random import randint, choices, random

CASE_SEP = '**** ****'

def merge(l1: list, l2: list) -> list: 
    out = []
    i = 0
    j = 0
    while i < len(l1) and j < len(l2):
        if l1[i] <= l2[j]:
            out.append(l1[i])
            i += 1
        else: 
            out.append(l2[j])
            j += 1
    while i < len(l1):
        out.append(l1[i])
        i += 1
    while j < len(l2):
        out.append(l2[j])
        j += 1
    return out

def concate_list(l: list[list]) -> str: 
    return [str(elem) for elem in sum(l, [])]

def merge_sort(l: list) -> list[str]: 
    l = l.copy()
    process: list[str] = []
    process.append(' '.join([str(elem) for elem in l]))
    
    div_lists = [[elem] for elem in l]
    while len(div_lists) > 1:
        for i in range(0, len(div_lists), 2):
            if i + 1 < len(div_lists):
                div_lists[i] = merge(div_lists[i], div_lists[i+1])
        div_lists = [div_lists[i] for i in range(0, len(div_lists), 2)]
        process.append(' '.join(concate_list(div_lists)))
    return process

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in range(args.N):
        length = randint(args.min_length, args.max_length)
        org = []
        for _ in range(length): 
            org.append(randint(1, 99))
        process_list = merge_sort(org)

        inputs = [f"('insertion', {elem})" for elem in org]
        inputs.append("('mergeSort', NULL)")
        cases.append(
            (
                ','.join(inputs), 
                '\n'.join(process_list)
            )
        )
    print((f'\n{CASE_SEP}\n').join([f'{tup[0]}\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='Test Case Gen for PA3 Task 1: Insertion Sort')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min-length', '-m', type=int, required=True, help='The minimum length of the string')
    parser.add_argument('--max-length', '-M', type=int, required=True, help='The maximum length of the string')
    args = parser.parse_args()
    main(args)
