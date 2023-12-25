#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647
using namespace std;
#include <algorithm>

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */
  
DisjointSets::DisjointSets() {
  for (int i = 0; i < NodeMaxCount; i++) {
    parent[i] = i;
    rank[i] = 0;
  }
}

int DisjointSets::find(int u) {
  if (u == parent[u]) return u;
  return parent[u] = find(parent[u]);
}

void DisjointSets::merge(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v) return;
  if (rank[u] > rank[v]) std::swap(u, v);
  parent[u] = v;
  if (rank[u] == rank[v]) rank[v]++;
}

PriorityQueue::PriorityQueue() {
  size = 0;
}

void PriorityQueue::push(int u) {
  arr[size++] = u;
  std::sort(arr, arr + size, [](const int &a, const int &b) {
    return a > b;
  });
}
int PriorityQueue::pop() {
  return arr[--size];
}

int to_int(std::string vertex_name) {
  return vertex_name[0] - 'A';
}

char to_char(int vertex) {
  return (char) (vertex + 'A');
}

bool Graph::is_vertex(int vertex) {
  return exist[vertex];
}

void Graph::dfs(int v, bool visited[V]) {
  visited[v] = true;
  for (int i = 0; i < V; i++) {
    if (edge[v][i] == 1 && !visited[i]) {
      dfs(i, visited);
    }
  }
}

void Graph::cycle_dfs(int v, bool visited[V], bool recStack[V], int &cycles) {
  visited[v] = true;
  recStack[v] = true;
  for (int i = 0; i < V; i++) {
    if (!is_vertex(i)) continue;
    if (edge[v][i] == 1) {
      if (!visited[i]) {
        cycle_dfs(i, visited, recStack, cycles);
      } else if (recStack[i]) {
        cycles++;
      }
    }
  }
  recStack[v] = false;
}

bool Graph::reachable(int start, int end) {
  if (start == end) return true;
  bool visited[V] = {0};
  dfs(start, visited);
  return visited[end];
}

int Graph::runKruskal() {
  std::cout << "HERE" << std::endl;
  for (int i = 0; i < V; i++) for (int j = 0; j < V; j++) mst[i][j] = 0;

  int n_edges = 0;
  int n_vertices = 0;
  for (int i = 0; i < V; i++) {
    if (is_vertex(i)) n_vertices++;
  }
  
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < i; j++) { // ignore self-loop
      if (edge[i][j] > 0) n_edges++;
    }
  }
  
  WeightedEdge edges[n_edges];
  
  int index = 0;
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < i; j++) { // ignore self-loop
      if (edge[i][j] > 0) {
        if (i > j) edges[index++] = { j, i, edge[i][j] };
        else edges[index++] = { i, j, edge[i][j] };
      }
    }
  }

  std::sort(edges, edges + n_edges, [](const WeightedEdge &a, const WeightedEdge &b) {
    if (a.weight != b.weight) return a.weight < b.weight;
    if (a.src != b.src) return a.src < b.src;
    return a.dest < b.dest;
  });

  int n_mst_edges = 0;
  int mst_weight = 0;

  WeightedEdge mst_edges[n_vertices - 1];
  index = 0;

  DisjointSets ds;
  for (int i = 0; i < n_edges; i++) {
    int u = edges[i].src;
    int v = edges[i].dest;
    int set_u = ds.find(u);
    int set_v = ds.find(v);
    if (set_u != set_v) {
      mst_edges[index] = edges[i];
      if (mst_edges[index].src > mst_edges[index].dest)
        std::swap(mst_edges[index].src, mst_edges[index].dest);
      index++;

      ds.merge(set_u, set_v);
      n_mst_edges++;
      mst_weight += edges[i].weight;
    }
  }

  std::sort(mst_edges, mst_edges + n_mst_edges, [](const WeightedEdge &a, const WeightedEdge &b) {
    return a.src < b.src;
  });

  for (int i = 0; i < n_mst_edges; i++) {
    int s = mst_edges[i].src, d = mst_edges[i].dest, w = mst_edges[i].weight;
    mst[s][d] = mst[d][s] = w;
  }

  return mst_weight;
}

std::string Graph::dfs_mst(int s, int d, bool visited[V], std::string path) {
  visited[s] = true;
  path += to_char(s);
  path += " ";
  if (s == d) return path;
  for (int i = 0; i < V; i++) {
    if (mst[s][i] > 0 && !visited[i]) {
      std::string result = dfs_mst(i, d, visited, path);
      if (result != "") return result;
    }
  }
  return "";
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

/////////1,2

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  edge[to_int(nodeA)][to_int(nodeB)] = 1;
  edge[to_int(nodeB)][to_int(nodeA)] = 1;
  exist[to_int(nodeA)] = 1;
  exist[to_int(nodeB)] = 1;
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countConnectedComponents() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  bool visited[V] = {0};
  int count = 0;
  for (int i = 0; i < V; i++) {
    if (!is_vertex(i)) continue;
    if (!visited[i]) {
      dfs(i, visited);
      count++;
    }
  }
  return count;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countBridge() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int n_bridges = 0;
  int prev = countConnectedComponents();
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < i; j++) { // assume that there is no self-loop
      if (edge[i][j] == 1) {
        // remove the edge
        edge[i][j] = 0;
        edge[j][i] = 0;
        int after = countConnectedComponents();
        if (prev < after) n_bridges++;
        edge[i][j] = 1;
        edge[j][i] = 1;
      }
    }
  }
  return n_bridges;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

/////////3,4

int Graph::addDirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  edge[to_int(nodeA)][to_int(nodeB)] = 1;
  exist[to_int(nodeA)] = 1;
  exist[to_int(nodeB)] = 1;
  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getTopologicalSort() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
  int in_degeee[V] = {0};
  for (int i = 0; i < V; i++) {
    if (!is_vertex(i)) continue;
    for (int j = 0; j < V; j++) {
      if (!is_vertex(j)) continue;
      if (edge[i][j] == 1) in_degeee[j]++;
    }
  }
  
  std::string scc = StrongConnectedComponents();
  int scc_count = 0;
  for (int i = 0; i < scc.length(); i++) {
    if (scc[i] == '\n') scc_count++;
  }

  int v_count = 0;
  for (int i = 0; i < V; i++) {
    if (is_vertex(i)) v_count++;
  }

  if (scc_count < v_count) return "Error"; // cycle detected

  PriorityQueue pq;
  int s_count = 0;
  for (int i = 0; i < V; i++) {
    if (!is_vertex(i)) continue;
    if (in_degeee[i] == 0) {
      pq.push(i);
      s_count++;
    }
  }
  
  if (v_count > 0 && s_count == 0) return "Error"; // cycle detected

  std::string result = "";
  
  while (pq.size > 0) {
    int cur = pq.pop();
    result += to_char(cur);
    result += " ";
    for (int i = 0; i < V; i++) {
      if (!is_vertex(i)) continue;
      if (edge[cur][i] == 1) {
        in_degeee[i]--;
        if (in_degeee[i] == 0) pq.push(i);
      }
    }
  }

  return result;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countDirectedCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
  int n_cycles = 0;
  
  bool visited[V] = {0};
  bool recStack[V] = {0};
  for (int i = 0; i < V; i++) {
    if (!is_vertex(i)) continue;
    if (!visited[i]) {
      cycle_dfs(i, visited, recStack, n_cycles);
    }
  }

  return n_cycles;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::StrongConnectedComponents() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  bool is_scc[V] = {0};
  std::string result = "";
  
  for (int i = 0; i < V; i++) {
    if (!is_vertex(i) || is_scc[i]) continue;
    
    std::string cur = "";
    for (int j = 0; j < V; j++) {
      if (!is_vertex(j) || is_scc[j]) continue;
      if (reachable(i, j) && reachable(j, i)) {
        cur += to_char(j);
        cur += " ";
        is_scc[j] = true;
      }
    }
    if (cur != "") {
      result += cur;
      result += "\n";
    }
  }
  return result;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

// 5

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  directGraph[to_int(nodeA)][to_int(nodeB)] = weight;
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::dijkstra(string source, int budget, ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
  bool S[V] = {0};
  int D[V];
  for (int i = 0; i < V; i++) D[i] = INT_MAX;

  int s = to_int(source);
  D[s] = 0;

  for (int i = 0; i < V; i++) {
    if (i == s) continue;
    if (directGraph[s][i] > 0)
      D[i] = directGraph[s][i];
  }

  for (int i = 0; i < V; i++) {
    if (i == s) continue;
    
    int min = INT_MAX;
    int min_index = -1;
    for (int j = 0; j < V; j++) {
      if (!S[j] && D[j] < min) {
        min = D[j];
        min_index = j;
      }
    }

    if (min_index == -1) break;
    S[min_index] = true;

    for (int j = 0; j < V; j++) {
      if (!S[j] && directGraph[min_index][j] > 0 && D[min_index] + directGraph[min_index][j] < D[j]) {
        D[j] = D[min_index] + directGraph[min_index][j];
      }
    }
  }

  pa5_answer = "";
  for (int i = 0; i < V; i++) {
    if (D[i] > 0 && D[i] <= budget) {
      pa5_answer += to_char(i);
      pa5_answer += " " + std::to_string(D[i]) + "\n";
    }
  }

  fout << pa5_answer;

  return pa5_answer;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

/// 6, 7

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  edge[to_int(nodeA)][to_int(nodeB)] = weight;
  edge[to_int(nodeB)][to_int(nodeA)] = weight;
  exist[to_int(nodeA)] = 1;
  exist[to_int(nodeB)] = 1;
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int mst_weight = runKruskal();

  for (int i = 0; i < V; i++) {
    for (int j = i + 1; j < V; j++) { // ignore self-loop
      if (mst[i][j] > 0) {
        fout << to_char(i) << " " << to_char(j) << " " << mst[i][j] << std::endl;
      }
    }
  }

  return mst_weight;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void Graph::findMinCostPath(string start, string end, ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  runKruskal();
  int s = to_int(start);
  int e = to_int(end);
  
  bool visited[V] = {0};
  std::string path = "";
  std::string result = dfs_mst(s, e, visited, path);
  
  int sum = 0;
  for (int i = 0; i < result.length() - 2; i++) {
    if (result[i] == ' ') continue;
    char cur_c = result[i];
    char next_c = result[i + 2];
    int cur = to_int(std::string() + cur_c);
    int next = to_int(std::string() + next_c);
    int weight = mst[cur][next];
    sum += weight;
    fout << cur_c << " " << next_c << " " << weight << std::endl;
  }

  fout << sum << std::endl;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}