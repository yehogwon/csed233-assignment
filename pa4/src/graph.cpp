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

int to_int(std::string vertex_name) {
  return vertex_name[0] - 'A';
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

bool Graph::reachable(int start, int end) {
  if (start == end) return true;
  bool visited[V] = {0};
  dfs(start, visited);
  return visited[end];
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
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < i; j++) { // assume that there is no self-loop
      if (edge[i][j] == 1) {
        int prev = countConnectedComponents();
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

  return "";

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countDirectedCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::StrongConnectedComponents() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  std::string scc[V];
  bool is_scc[V] = {0};

  std::string result = "";
  for (int i = 0; i < V; i++) {
    if (!is_vertex(i) || is_scc[i]) continue;
    
    std::string cur = "";
    for (int j = 0; j < V; j++) {
      if (!is_vertex(j) || is_scc[j]) continue;
      if (reachable(i, j) && reachable(j, i)) {
        cur += (char)(j + 'A');
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
    if (D[i] > 0 && D[i] < budget) {
      pa5_answer += (char) (i + 'A');
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

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void Graph::findMinCostPath(string start, string end, ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  return;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}