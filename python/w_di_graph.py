import argparse
from random import randint, choices, random

CASE_SEP = '**** ****'

V = 26

class WeightedDirectedGraph: 
    def __init__(self) -> None: 
        self.adj_matrix = [[0 for _ in range(V)] for _ in range(V)]
    
    def is_vertex(self, v: int) -> bool:
        return 1 in self.adj_matrix[v] or 1 in [self.adj_matrix[i][v] for i in range(V)]
    
    def add_edge(self, v: int, w: int, weight: int) -> None:
        self.adj_matrix[v][w] = weight

    def remove_edge(self, v: int, w: int) -> None:
        self.adj_matrix[v][w] = 0

    def has_edge(self, v: int, w: int) -> bool:
        return self.adj_matrix[v][w] > 0

    def dijkstra(self, s: int) -> list:
        dist = [float('inf') for _ in range(V)]
        dist[s] = 0
        visited = [False for _ in range(V)]
        for _ in range(V):
            u = -1
            for i in range(V):
                if not visited[i] and (u == -1 or dist[i] < dist[u]):
                    u = i
            visited[u] = True
            for v in range(V):
                if self.adj_matrix[u][v] > 0 and not visited[v]:
                    dist[v] = min(dist[v], dist[u] + self.adj_matrix[u][v])
        return dist

def to_char(v: int) -> str:
    return chr(ord('A') + v)

def main(args: argparse.Namespace) -> None:
    cases = []
    for _ in range(args.N):
        length = randint(args.min_length, args.max_length)
        pairs = []
        g = WeightedDirectedGraph()
        v = randint(args.min_V, args.max_V)
        for _ in range(length): 
            w = randint(1, 15)
            s, d = -1, -1
            _attempts = 0
            while s == d or g.has_edge(s, d):
                if _attempts > 1000:
                    break
                s, d = randint(0, v - 1), randint(0, v - 1)
                _attempts += 1
            if _attempts > 1000:
                continue
            pairs.append((s, d, w))
            g.add_edge(s, d, w)
        budget = randint(1, 15)
        start = pairs[randint(0, len(pairs) - 1)][0]
        dist = g.dijkstra(start)
        answers = []
        for i in range(v):
            if dist[i] <= budget and i != start:
                answers.append((i, dist[i]))

        cases.append(
            (
                ', '.join([f"('{to_char(s)}-{to_char(d)}',{w})" for s, d, w in pairs] + [f"('{to_char(start)}', {str(budget)})"]),
                '\n'.join([f'{to_char(v)} {d}' for v, d in answers])
            )
        )
    print((f'\n{CASE_SEP}\n').join([f'[{tup[0]}]\n{tup[1]}' for tup in cases]))
    print(CASE_SEP)

if __name__ == '__main__': 
    parser = argparse.ArgumentParser(description='PA4 Dijkstra Test Case Generator')
    parser.add_argument('-N', type=int, required=True, help='The number of samples to generate')
    parser.add_argument('--min_length', type=int, required=True, help='The minimum length of the instruction')
    parser.add_argument('--max_length', type=int, required=True, help='The maximum length of the instruction')
    parser.add_argument('--min_V', type=int, required=True, help='The value of vertices')
    parser.add_argument('--max_V', type=int, required=True, help='The value of vertices')
    args = parser.parse_args()
    main(args)
