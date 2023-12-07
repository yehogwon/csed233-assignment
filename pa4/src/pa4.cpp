#include "graph.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

/*
    [Task 1] Undirected Graph - Connected Component Count

    Description:
        Implement a function that returns the number of connected components in
   the given undirected graph. You can modify graph.cpp and graph.h files for
   this problem.

        TODO: Implement Graph::addUndirectedEdge,
   Graph::countConnectedComponents

    Input & output
    Input: Pairs of nodes with alphabet labels that indicate edges.
        - ('A','B'): an edge between node A and node B.
                    The names of the nodes are restricted to uppercase
   alphabetic characters.
        - If the input edge already exists in the graph, ignore the input.
    Output:
        - The number of connected components in the given undirected graph

*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 1]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addUndirectedEdge(firstNode, secondNode);
    }
    fout << graph.countConnectedComponents() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 2] Undirected Graph - Bridge Count

    Description:
        In graph theory, bridge is an edge of a graph whose deletion increases
   the graph's number of connected components. Implement a function that returns
   the number of bridges in the given undirected graph. You can modify graph.cpp
   and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge, which is implemented at the
   task 1, and Graph::countBridge functions.

    Input & output
    Input: Pairs of nodes with alphabet labels that indicate edges.
        - ('A','B'): an edge between node A and node B.
                    The names of the nodes are restricted to uppercase
   alphabetic characters.
        - If the input edge already exists in the graph, ignore the input.
    Output:
        - The number of bridge in the given undirected graph
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 2]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addUndirectedEdge(firstNode, secondNode);
    }
    fout << graph.countBridge() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 3] Directed Graph - Topological Sort and Cycle Count (2pts)

    Description:
        Implement a function that performs a topological sort using the given
   directed graph. If there exists more than one result, print the topological
   sort that comes first in the ascending order. To take an example below,
   acceptable topological sorts are ‘A B C D F E’, ‘A C B F E D’, ‘A C D B F E’,
   etc. Among these, the desirable output is ‘A B C D F E’. Also, print ‘Error’
   if the topological sort could not be performed, and the number of cycles. You
   can modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addDirectedEdge, Graph::getTopologicalSort and
   Graph::countDirectedCycle functions

    Input & output
    Input: Pairs of node labels that indicate edges.
        - ('A', 'B'): an edge from node A to node B.
        - If the input edge already exists in the graph, ignore the input.
    Output:
        - Result of topological sort or ‘error’ message with number of cycles.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 3]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addDirectedEdge(firstNode, secondNode);
    }

    if (graph.getTopologicalSort() == "Error") {
      fout << graph.getTopologicalSort() << endl;
      fout << graph.countDirectedCycle() << endl;
    } else {
      fout << graph.getTopologicalSort() << endl;
    }

  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 4] Directed Graph - Cycle Count

    Description:
        Implement a function that returns the strongly connected components in
   the given directed graph. Print the strongly connected components in the
   ascending order. You can modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addDirectedEdge, which is implemented at the task
   3, and Graph::StrongConnectedComponents functions.

    Input & output
    Input: Pairs of node labels that indicate edges.
        - ('A', 'B'): an edge from node A to node B.
        - If the input edge already exists in the graph, ignore the input.
    Output:
        - Strongly connected components in ascending order.
          Each strongly connected components are separated with Enter as shown
   in Output examples. (Check the Document)
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 4]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addDirectedEdge(firstNode, secondNode);
    }

    fout << graph.StrongConnectedComponents() << endl;

  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 5] Dijkstra's Algorithm

    Description:
       Implement a function that finds paths from the source node to all other
   nodes that the total cost of path is lower that the given budget. We assume
   that the given graph is a directed, weighted, and weakly-connected graph. All
   weights of edges are positive (i.e. larger than 0). This function should
   return the pair of the reachable destination node and the total cost (sum of
   the weights of the edges) of the path.If the path from the source node to the
   destination node doesn't exist, return a empty line. You can modify the
   graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addDirectedEdge and Graph::getShortestPath
   functions

    Input & output
    Input: A sequence of commands
        - ('A-B', integer): an edge from node A to node B with weight
   value{integer}.
        - ('A', integer): The first element indicates the source node and the
   second integer indicates the allowed budget.
   Output:
        - Pairs of the destination node and the total cost of the path.
        (the sequence of pairs should be in lexicographical order.)
        (node and cost separated with space.)
        - An empty line if the path does not exist. (It should include '\n', a
   newline character.)
 */

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 5]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength() - 1; i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      int value = instr_seq.getInstruction(i).getValue();
      string firstNode = command.substr(0, command.find('-'));
      string secondNode =
          command.substr(command.find('-') + 1, command.length());
      graph.addDirectedEdge(firstNode, secondNode, value);
    }

    string command =
        instr_seq.getInstruction(instr_seq.getLength() - 1).getCommand();
    string source = command;
    int budget = instr_seq.getInstruction(instr_seq.getLength() - 1).getValue();
    graph.dijkstra(source, budget, fout);
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 6] Kruskal's Algorithm

    Description:
        Implement a function that finds the Minimum-cost Spanning Tree (MST) of
   the given weighted undirected graph using the Kruskal's algorithm. The
   function prints the added edge and the weight of the edge each time the tree
   grows. When printing an edge, you have to print the label in lexicographical
   order. If there are multiple edges with the same weight, this function also
   selects the edge in lexicographical order. That means it compares the first
   node of edges, and if the first node is the same, it compares the second node
   of edges. The function return the cost of the MST (i.e. the sum of edge
   weights). You can assume that the given graph is a connected graph. You can
   modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge and Graph::kruskalMST functions

    Input & output
    Input: A sequence of commands
        - ('A-B', integer): an edge between node A and node B with weight value
   {integer}.
        - ('MST', NULL): find MST using the Kruskal's algorithm.
    Output:
        - For each time the tree grows, print the labels of the nodes indicating
   the added edges in lexicographical order and the weight of the edge as a
   string separated with a white space.
        - Print the cost of MST.
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 6]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("MST") == 0) {
        fout << graph.kruskalMST(fout) << endl;
      } else {
        string firstNode = command.substr(0, command.find('-'));
        string secondNode =
            command.substr(command.find('-') + 1, command.length());
        int value = instr_seq.getInstruction(i).getValue();
        graph.addUndirectedEdge(firstNode, secondNode, value);
      }
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 7] Finding the Path of MST

    Description:
        Implement a function that determines the path between two specified
   nodes in the Minimum Spanning Tree (MST). Once the MST is obtained using
   Kruskal's algorithm, this function identifies the minimum-cost path between
   the given nodes. Assume that the given graph is a connected graph. You may
   modify the graph.cpp and graph.h files for this problem. (Note: This problem
   relies on Task 7; ensure that Task 7 is successfully implemented for this
   problem.)

        TODO: Implement Graph::addUndirectedEdge and Graph::findMinCostPath
   functions

    Input & output
    Input: A sequence of commands
        -	('A-B', integer): an edge between node A and node B with a
   weight value of {integer}. -	('PATH-A-B', NULL): find the minimum-cost path
   of MST after performing the Kruskal's algorithm

    Output:
        -	Print the calculated path ([source node] [destination node]
   [weight]) -	Print the cost of the path


*/

void task_7(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 7]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare(0, 4, "PATH") == 0) {
        string firstNode = command.substr(5, 1);
        string secondNode = command.substr(7, 1);

        graph.findMinCostPath(firstNode, secondNode, fout);
      } else {
        string firstNode = command.substr(0, command.find('-'));
        string secondNode =
            command.substr(command.find('-') + 1, command.length());
        int value = instr_seq.getInstruction(i).getValue();
        graph.addUndirectedEdge(firstNode, secondNode, value);
      }
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

#ifndef DOING_CTEST // SUBMIT: REMOVE THIS LINE
int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence instr_seq;

  // Open file
  ofstream fout;
  fout.open(filename, fstream::app);
  if (!fout.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }

  // Choosing task number. Default is running ALL tasks (0)
  if (argc >= 2)
    task_num = atoi(argv[1]);
  if (argc >= 3) {
    try {
      instr_seq.parseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout, instr_seq);
    break;
  case 2:
    task_2(fout, instr_seq);
    break;
  case 3:
    task_3(fout, instr_seq);
    break;
  case 4:
    task_4(fout, instr_seq);
    break;
  case 5:
    task_5(fout, instr_seq);
    break;
  case 6:
    task_6(fout, instr_seq);
    break;
  case 7:
    task_7(fout, instr_seq);
    break;
  case 0:
    instr_seq.parseInstructions(TASK_1_DEFAULT_ARGUMENT);
    task_1(fout, instr_seq);

    instr_seq.parseInstructions(TASK_2_DEFAULT_ARGUMENT);
    task_2(fout, instr_seq);

    instr_seq.parseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq);

    instr_seq.parseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq);

    instr_seq.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq);

    instr_seq.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq);

    instr_seq.parseInstructions(TASK_7_DEFAULT_ARGUMENT);
    task_7(fout, instr_seq);

    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
#endif // SUBMIT: REMOVE THIS LINE