from typing import List, Tuple
import sys

def find(parent: List[int], i: int) -> int:
    if parent[i] == i:
        return i
    return find(parent, parent[i])

def union(parent: List[int], rank: List[int], x: int, y: int) -> None:
    xroot = find(parent, x)
    yroot = find(parent, y)

    if rank[xroot] < rank[yroot]:
        parent[xroot] = yroot
    elif rank[xroot] > rank[yroot]:
        parent[yroot] = xroot
    else:
        parent[yroot] = xroot
        rank[xroot] += 1

def kruskal(vertices: int, edges: List[Tuple[int, int, int]]) -> Tuple[int, List[Tuple[int, int, int]]]:
    result = [] # DEBUGGING
    total_weight = 0

    # Sort edges in descending order of weight
    edges.sort(key=lambda x: x[2], reverse=True)

    parent = [i for i in range(vertices+1)]
    rank = [0 for _ in range(vertices+1)]

    for i in range(len(edges)):
        u, v, w = edges[i]
        parent_u = find(parent, u)
        parent_v = find(parent, v)

        if parent_u != parent_v:
            total_weight += w
            result.append((u, v, w)) # DEBUGGING
            union(parent, rank, parent_u, parent_v)
    
    return total_weight, result

def main() -> None:
    with open(sys.argv[1], 'r') as f:
        vertices = int(f.readline().strip())
        edges = []
        for _ in range(int(f.readline().strip())):
            u, v, w = map(int, f.readline().strip().split())
            edges.append((u, v, w))
    
    total_weight, mst = kruskal(vertices, edges)
    print(f'Maximum spanning tree: {mst}')
    print(f'Total weight: {total_weight}')

if __name__ == '__main__':
    main()
