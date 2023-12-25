import argparse
from random import randint, choices, random
import networkx as nx
from tqdm import tqdm

CASE_SEP = '**** ****'

V = 26

class UndirectedGraph: 
    def __init__(self) -> None: 
        self.adj_matrix = [[0 for _ in range(V)] for _ in range(V)]
    
    def is_vertex(self, v: int) -> bool:
        return 1 in self.adj_matrix[v]
    
    def add_edge(self, v: int, w: int) -> None:
        self.adj_matrix[v][w] = 1
        self.adj_matrix[w][v] = 1

    def remove_edge(self, v: int, w: int) -> None:
        self.adj_matrix[v][w] = 0
        self.adj_matrix[w][v] = 0
    
    def dfs(self, v: int, visited: list) -> None:
        visited[v] = True
        for w in range(V):
            if not self.is_vertex(w):
                continue
            if self.adj_matrix[v][w] == 1 and not visited[w]:
                self.dfs(w, visited)
    
    def connected_components(self) -> int:
        visited = [False for _ in range(V)]
        count = 0
        for v in range(V):
            if not self.is_vertex(v):
                continue
            if not visited[v]:
                self.dfs(v, visited)
                count += 1
        return count
    
    def bridges(self) -> int: 
        g = nx.Graph()
        for v in range(V):
            if not self.is_vertex(v):
                continue
            for w in range(V):
                if not self.is_vertex(w):
                    continue
                if self.adj_matrix[v][w] == 1:
                    g.add_edge(v, w)
        return len(list(nx.bridges(g)))

def to_char(v: int) -> str:
    return chr(ord('A') + v)

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in tqdm(range(args.N)):
        length = randint(args.min_length, args.max_length)
        pairs = []
        g = UndirectedGraph()
        for _ in range(length): 
            s, d = -1, -1
            _attempts = 0
            while s == d or (s, d) in pairs:
                if _attempts > 1000:
                    break
                s, d = randint(0, V - 1), randint(0, V - 1)
                _attempts += 1
            if _attempts > 1000:
                continue
            pairs.append((s, d))
            g.add_edge(s, d)
        if args.mode == 'cc': 
            answer = str(g.connected_components())
        elif args.mode == 'brdg':
            answer = str(g.bridges())

        cases.append(
            (
                ', '.join([f"('{to_char(s)}', '{to_char(d)}')" for s, d in pairs]),
                str(answer)
            )
        )
    print((f'\n{CASE_SEP}\n').join([f'[{tup[0]}]\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='PA4 Undirected Graph Test Case Generator')
    parser.add_argument('--mode', type=str, choices=['cc', 'brdg'], required=True, help='The mode of problem to the test case generator')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min_length', type=int, required=True, help='The minimum length of the instruction')
    parser.add_argument('--max_length', type=int, required=True, help='The maximum length of the instruction')
    args = parser.parse_args()
    main(args)
