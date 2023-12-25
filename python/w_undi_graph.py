import argparse
from random import randint, choices, random
import numpy as np
import networkx as nx
from tqdm import tqdm

CASE_SEP = '**** ****'

V = 26

class DisjointSet:
    def __init__(self, n: int) -> None:
        self.parent = [i for i in range(n)]
        self.rank = [0 for _ in range(n)]
    
    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x: int, y: int) -> None:
        x_root, y_root = self.find(x), self.find(y)
        if x_root == y_root:
            return
        if self.rank[x_root] < self.rank[y_root]:
            self.parent[x_root] = y_root
        elif self.rank[x_root] > self.rank[y_root]:
            self.parent[y_root] = x_root
        else:
            self.parent[y_root] = x_root
            self.rank[x_root] += 1

class WeightedUndirectedGraph: 
    def __init__(self) -> None: 
        self.adj_matrix = [[0 for _ in range(V)] for _ in range(V)]
    
    def vertices(self) -> list: 
        return [v for v in range(V) if self.is_vertex(v)]
    
    def is_vertex(self, v: int) -> bool:
        return True in [True if self.adj_matrix[v][w] != 0 else False for w in range(V)]
    
    def is_edge(self, s: int, e: int) -> bool: 
        return self.adj_matrix[s][e] != 0
    
    def add_edge(self, v: int, w: int, weight: int) -> None:
        self.adj_matrix[v][w] = weight
        self.adj_matrix[w][v] = weight

    def remove_edge(self, v: int, w: int) -> None:
        self.adj_matrix[v][w] = 0
        self.adj_matrix[w][v] = 0
    
    def dfs(self, v: int, visited: list) -> None:
        visited[v] = True
        for w in range(V):
            if not self.is_vertex(w):
                continue
            if self.adj_matrix[v][w] != 0 and not visited[w]:
                self.dfs(w, visited)
    
    def connected(self) -> bool: 
        visited = [False for _ in range(V)]
        min_v = -1
        for v in range(V):
            if self.is_vertex(v):
                min_v = v
                break
        if min_v == -1:
            return True
        self.dfs(min_v, visited)
        return sum(visited) == sum([True if self.is_vertex(v) else False for v in range(V)])
    
    def kruskal(self) -> list: 
        edges = []
        for v in range(V):
            for w in range(V):
                if self.adj_matrix[v][w] != 0:
                    edges.append((v, w, self.adj_matrix[v][w]))
        edges.sort(key=lambda x: x[2])
        ds = DisjointSet(V)
        mst = []
        for edge in edges:
            v, w, weight = edge
            if ds.find(v) != ds.find(w):
                ds.union(v, w)
                mst.append(edge)
        mst = sorted(mst, key=lambda x: (x[0], x[1]))
        self.mst = mst
        return sum([edge[2] for edge in mst])

def to_char(v: int) -> str:
    return chr(ord('A') + v)

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in tqdm(range(args.N)): 
        length = randint(args.min_length, args.max_length)
        pairs = []
        g = WeightedUndirectedGraph()
        v = randint(args.min_V, args.max_V)
        while True: 
            pairs = []
            g = WeightedUndirectedGraph()
            for _ in range(length): 
                w = randint(1, 15)
                s, d = -1, -1
                _attempts = 0
                while s == d or g.is_edge(s, d):
                    if _attempts > 1000:
                        break
                    s, d = randint(0, v - 1), randint(0, v - 1)
                    _attempts += 1
                if _attempts > 1000:
                    continue
                pairs.append((s, d, w))
                g.add_edge(s, d, w)
            if g.connected():
                break
        cost = g.kruskal()
        if args.mode == 'mst': 
            inp = ', '.join([f"('{to_char(s)}-{to_char(d)}',{w})" for s, d, w in pairs] + ["('MST', NULL)"])
            answer = '\n'.join([f'{to_char(s)} {to_char(d)} {w}' for s, d, w in g.mst] + [str(cost)])
        else: 
            s, d = choices(g.vertices(), k=2)
            while s == d: 
                s, d = choices(g.vertices(), k=2)
            inp = ', '.join([f"('{to_char(s)}-{to_char(d)}',{w})" for s, d, w in pairs] + [f"('PATH-{to_char(s)}-{to_char(d)}', NULL)"])

            mst_adj_matrix = np.zeros((V, V), dtype=int)
            for x, y, w in g.mst:
                mst_adj_matrix[x][y] = w
                mst_adj_matrix[y][x] = w
            mst_graph = nx.Graph(mst_adj_matrix)
            path = nx.shortest_path(mst_graph, s, d)

            trace = []
            for i in range(len(path) - 1):
                trace.append((path[i], path[i + 1], mst_adj_matrix[path[i]][path[i + 1]]))
            answer = '\n'.join([f'{to_char(s)} {to_char(d)} {w}' for s, d, w in trace] + [str(sum([w for _, _, w in trace]))])

        cases.append((inp, answer))
    print((f'\n{CASE_SEP}\n').join([f'[{tup[0]}]\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='PA4 Undirected Weighted Graph Test Case Generator')
    parser.add_argument('--mode', type=str, choices=['mst', 'path'], required=True, help='The mode of the test case generator')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min_length', type=int, required=True, help='The minimum length of the instruction')
    parser.add_argument('--max_length', type=int, required=True, help='The maximum length of the instruction')
    parser.add_argument('--min_V', type=int, required=True, help='The minimum number of vertices')
    parser.add_argument('--max_V', type=int, required=True, help='The maximum number of vertices')
    args = parser.parse_args()
    main(args)
