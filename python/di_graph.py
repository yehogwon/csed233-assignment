import argparse
from random import randint, choices, random
import networkx as nx
import numpy as np
from tqdm import tqdm

CASE_SEP = '**** ****'

V = 26

class DirectedGraph: 
    def __init__(self) -> None: 
        self.adj_matrix = [[0 for _ in range(V)] for _ in range(V)]
    
    def is_vertex(self, v: int) -> bool:
        return 1 in self.adj_matrix[v] or 1 in [self.adj_matrix[i][v] for i in range(V)]
    
    def add_edge(self, v: int, w: int) -> None:
        self.adj_matrix[v][w] = 1

    def remove_edge(self, v: int, w: int) -> None:
        self.adj_matrix[v][w] = 0

    def strongly_connected_components(self) -> list[list]: 
        g = nx.DiGraph(np.array(self.adj_matrix))
        sccs = list(nx.strongly_connected_components(g))
        for i in range(len(sccs)): 
            sccs[i] = [v for v in list(sccs[i]) if self.is_vertex(v)]
        sccs = [scc for scc in sccs if len(scc) > 0]
        sccs = [sorted(scc) for scc in sccs]
        sccs.sort()
        return sccs

def to_char(v: int) -> str:
    return chr(ord('A') + v)

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in tqdm(range(args.N)):
        length = randint(args.min_length, args.max_length)
        pairs = []
        v = randint(args.min_V, args.max_V)
        g = DirectedGraph()
        for _ in range(length): 
            s, d = -1, -1
            _attempts = 0
            while s == d or (s, d) in pairs:
                if _attempts > 1000:
                    break
                s, d = randint(0, v - 1), randint(0, v - 1)
                _attempts += 1
            if _attempts > 1000:
                continue
            pairs.append((s, d))
            g.add_edge(s, d)
        if args.mode == 'tpsort': 
            answer = str(g.connected_components())
        elif args.mode == 'scc':
            sccs = g.strongly_connected_components()
            answer = '\n'.join([' '.join([to_char(v) for v in scc]) for scc in sccs])

        cases.append(
            (
                ', '.join([f"('{to_char(s)}', '{to_char(d)}')" for s, d in pairs]),
                str(answer)
            )
        )
    print((f'\n{CASE_SEP}\n').join([f'[{tup[0]}]\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='PA4 Directed Graph Test Case Generator')
    parser.add_argument('--mode', type=str, choices=['tpsort', 'scc'], required=True, help='The mode of problem to the test case generator')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min_length', type=int, required=True, help='The minimum length of the instruction')
    parser.add_argument('--max_length', type=int, required=True, help='The maximum length of the instruction')
    parser.add_argument('--min_V', type=int, required=True, help='The minimum value of vertices')
    parser.add_argument('--max_V', type=int, required=True, help='The maximum value of vertices')
    args = parser.parse_args()
    main(args)
