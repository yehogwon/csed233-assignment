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

  return "";

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

// 5

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::dijkstra(string source, int budget, ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

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