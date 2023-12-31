#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;
// Number of vertices in the graph
#define V 26
#define INT_MAX 1000000

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

struct DisjointSets {
  int parent[NodeMaxCount];
  int rank[NodeMaxCount];
  
  DisjointSets();
  int find(int u);
  void merge(int u, int v);
};

struct WeightedEdge {
  int src, dest, weight;
};

struct PriorityQueue {
  int arr[V]; // keep this array sorted in descending order
  int size;

  PriorityQueue();
  void push(int u);
  int pop();
};

int to_int(std::string vertex_name);
char to_char(int vertex);

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph(){};
  ~Graph(){};

  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  /////// 1, 2

  int addUndirectedEdge(string nodeA, string nodeB);
  int addUndirectedEdge(string nodeA, string nodeB, int weight);
  int countConnectedComponents();
  int countBridge();

  /////// 3, 4
  int addDirectedEdge(string nodeA, string nodeB);
  string getTopologicalSort();
  int countDirectedCycle();
  string StrongConnectedComponents();

  /////// 5, 6, 7
  int addDirectedEdge(string nodeA, string nodeB, int weight);
  string dijkstra(string source, int budget, ofstream &fout);

  int kruskalMST(ofstream &);
  void findMinCostPath(string start, string end, ofstream &f);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  int edge[100][100] = {0};
  int exist_edge[100][100] = {0};
  int node_num[100] = {
      -1,
  };
  int count = 0;
  bool exist[100] = {0};

  ///////1, 2

  ///////3, 4
  ///////5, 6, 7

  int directGraph[26][26] = {
      0,
  };

  int mst[26][26] = {
      0,
  };

  string pa5_answer;

  bool is_vertex(int vertex);
  void dfs(int v, bool visited[V]); // update visited
  void cycle_dfs(int v, bool visited[V], bool recStack[V], int &cycles);
  bool reachable(int start, int end);
  int runKruskal();
  std::string dfs_mst(int s, int d, bool visited[V], std::string path);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
