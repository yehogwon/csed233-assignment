/*
    Programming Assignment #2

*/
#include "heap.h"
#include "tree.h"
#include "utils.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
    [Task 1] Quiz

    // Image of tree is in the Programming Assignmnet 2 PDF file //
    1-1. For such tree, which has the correct pair for preorder traversal
        and post order traversal of the tree?

        (1)	Preorder : 1 2 4 5 6 3 7 9 8
            Postorder : 4 5 6 2 9 7 8 3 1
        (2)	Preorder : 4 5 6 2 9 7 8 3 1
            Postorder : 1 2 4 5 6 3 7 9 8
        (3)	Preorder : 1 2 4 5 6 3 7 9 8
            Postorder : 4 5 6 2 1 9 7 3 8
        (4)	None of the aboves



    1-2.  What is the time complexity of rearranging min-heap into max-heap?

          (1) O(1)
          (2) O(log n)
          (3) O(n)
          (4) O(2^n)

*/
void task_1(ofstream &fout, const char *quiz_num) {
    fout << "[Task 1]" << endl;
    int answer_1_1 = 1; // TODO: Change to your answer
    int answer_1_2 = 3; // TODO: Change to your answer

    if (!strcmp(quiz_num, "1")) {
        fout << answer_1_1 << endl;
    } else if (!strcmp(quiz_num, "2")) {
        fout << answer_1_2 << endl;
    } else {
        cerr << "Wrong quiz number:" << quiz_num << endl;
    }
}

/*
    [Task 2] Binary Tree and General Tree

    Description:
        Implement a function that prints the bracket representation of a general tree
        which is given as input in forms of the Left-Child/Right-Sibling binary tree.

    Input:
        - String with bracket representation of binary tree

    Output:
        - String with bracket representation of general k-ary tree.
*/

void task_2(ofstream &fout, const char *tree_string) {
    fout << "[Task 2]" << endl;
    try {
        BinaryTree tree;
        tree.buildFromString(tree_string);
        fout << tree.general_tree() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*

    [Task 3] Traverse Binary Tree (2 pts)

    Description:
        Print the expected sequence of values of tree traversal
        TODO: Implement BinaryTree::preOrder, BinaryTree::postOrder and BinaryTree::inOrder, \
            BinaryTree::levelOrder function that can traverse a binary tree with given traverse mode. \
            You can additionally implement other functions to facilitate the traversal of a binary tree \
            (HINT : BinaryTree::_currentLevel used in level order traverse mode.)

    Input:
        -	String with bracket representation.
        -	String representing traverse mode. Either “preorder”, “postorder”, “inorder”, or “levelorder”

    Output:
        -	A sequence of node values acquired from the tree traversal. The value is separated with a white space


*/
void task_3(ofstream &fout, const char *tree_string,
            const char *traverse_mode) {
    fout << "[Task 3]" << endl;
    try {
        BinaryTree tree;
        tree.buildFromString(tree_string);

        if (!strcmp(traverse_mode, "preorder")) {
            fout << tree.preOrder() << endl;
        } else if (!strcmp(traverse_mode, "postorder")) {
            fout << tree.postOrder() << endl;
        } else if (!strcmp(traverse_mode, "inorder")) {
            fout << tree.inOrder() << endl;
        } else if (!strcmp(traverse_mode, "levelorder")) {
            fout << tree.levelOrder() << endl;
        } else {
            cerr << "invalid traverse mode" << endl;
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 4] Properness of Binary Tree

    Description:
        We know that we can identify a binary tree uniquely by two traversal sequences.
        Rebuild a binary from given two traversals.
        You can use orderIndex, inorder, preorder, postorder, inorderIdx initialized above.

    Input:
        - argc: Number of given string.
        - argv: Two strings with integers divided by ‘,’ covered by brackets + Type of second traversal. "pre", "post".

    Output:
        - “error” if given traversals cannot identify a binary tree.
        - String of a binary tree of format introduced in pre-2.
*/
int orderIndex; // index of the root node of current subtree in preorder or postorder traversal
int inorder[100]; // inorder traversal
int order[100]; // preorder or postorder traversal
int inorderIdx[100]; // inorderIdx[x] = the index of x in inorder array. That is, inorder[inorderIdx[x]] = x

///////////////////////////////////////////////////////////////////////////////////////////////////
/////// NOTICE THAT I ADDED SOME CODES IN `task_4` FUNCTION TO DETECT ANY DUPLICATED VALUES ///////
///////////////////////////////////////////////////////////////////////////////////////////////////

// NOTE: Check if these tree reconstruction algorithms detect invalid trees well
string buildFromPreorder(int inLeft, int inRight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    int root_val = order[orderIndex++];
    int root_idx = inorderIdx[root_val];
    if (root_idx == -1 || root_idx < inLeft || root_idx > inRight) return "error"; // root is out of range
    if (inLeft == inRight) {
        if (inorder[inLeft] == root_val) return to_string(root_val);
        else return "error";
    }

    std::string left, right;
    if (root_idx - inLeft > 0) left = buildFromPreorder(inLeft, root_idx - 1);
    if (inRight - root_idx > 0) right = buildFromPreorder(root_idx + 1, inRight);

    if (left == "error" || right == "error") return "error";
    return to_string(root_val) + "(" + left + ")(" + right + ")";

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string buildFromPostorder(int inLeft, int inRight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    int root_val = order[orderIndex--];
    int root_idx = inorderIdx[root_val];
    if (root_idx == -1 || root_idx < inLeft || root_idx > inRight) return "error"; // root is out of range
    if (inLeft == inRight) {
        if (inorder[inLeft] == root_val) return to_string(root_val);
        else return "error";
    }

    std::string left, right;
    if (inRight - root_idx > 0) right = buildFromPostorder(root_idx + 1, inRight);
    if (root_idx - inLeft > 0) left = buildFromPostorder(inLeft, root_idx - 1);

    if (left == "error" || right == "error") return "error";
    return to_string(root_val) + "(" + left + ")(" + right + ")";

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void parseInput4(const char *str, int *arr) {
    char input[100];
    strcpy(input, str);
    char *token = strtok(input, "[,]");
    int index = 0;
    while (token != NULL) {
        arr[index++] = atoi(token);
        token = strtok(NULL, "[,]");
    }
}

void task_4(ofstream &fout, const char* argv[]) {
    fout << "[Task 4]" << endl;
    string answer;

    parseInput4(argv[0], inorder);
    int n = 0; // length of inorder
    while (inorder[n])
        n++;

    for (int i = 0; i < n; i++) {
        inorderIdx[inorder[i]] = i;
    }

    // Initialize with -1 to detect invalid values
    memset(inorderIdx, -1, sizeof(inorderIdx));
    for (int i = 0; i < n; i++) {
        inorderIdx[inorder[i]] = i;
    }
    parseInput4(argv[1], order);
    int m = 0; // length of order
    while (order[m])
        m++;

    if (n != m) { // invalid if two traversals have different lengths
        fout << "error" << endl;
        return;
    }

    // check if there is a duplicate value in the given inorder traversal
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (inorder[i] == inorder[j]) {
                fout << "error" << endl;
                return;
            }

    // check if there is a duplicate value in the given pre/postorder traversal
    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            if (order[i] == order[j]) {
                fout << "error" << endl;
                return;
            }

    // Compare type of traversal and choose proper function
    if (strcmp(argv[2], "pre") == 0) {
        orderIndex = 0;
        answer = buildFromPreorder(0, n - 1);
    } else if (strcmp(argv[2], "post") == 0) {
        orderIndex = n - 1;
        answer = buildFromPostorder(0, n - 1);
    } else {
        answer = "error";
    }
    fout << answer << endl;
}


/*
    [Task 5] Priority Queue Insertion

    Description:
        Insert a new element to a PriorityQueue
        Heap should maintain the property after the insertion.
        TODO: Implement PriorityQueue::insertion function
              Implement PriorityQueue::getMax function

    Input:
        (‘insert’,integer): insert an integer into the current priority queue
        (‘getMax’, anything): Return a value with the maximum priority
        (‘isEmpty’, anything): Return wheter the priority queue is currently empty.

    Output:
        Values in the heap in a node number order, in a string separated with
        the white space (automatically printed with built-in function)
        There will be no “error case” such as overflow, underflow.
*/
void task_5(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 5]" << endl;
    try
    {
        PriorityQueue pq;
        for (int i = 0; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0)
            {
                int input_value = instr_seq.getInstruction(i).getValue();

                /* BEGIN_YOUR_CODE*/
                if (!pq.insert(input_value, input_value)) {
                    fout << "Error";
                    return;
                }
                /* END_YOUR_CODE */
            }
            else if (command.compare("getMax") == 0)
            {
                /* BEGIN_YOUR_CODE*/
                if (pq.empty()) fout << "Empty" << " ";
                else fout << pq.getMax().value << " ";
                /* END_YOUR_CODE */
            }
            else if (command.compare("isEmpty") == 0)
            {
                /* BEGIN_YOUR_CODE*/
                fout << (pq.empty() ? "True" : "False") << " ";
                /* END_YOUR_CODE */
            }
            else
            {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << pq.printPQ() << endl;
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

/*
    [Task 6] Priority Queue Deletion

    Description:
        Delete the node having maximum priority from the Priority Queue
        Priority Queue should maintain the property after the deletion.
        TODO: Implement PriorityQueue::removeMax function

    Input:
        -	(‘removeMax’,NULL): delete the node having maximum priority from the priority queue.
    Output:
        Values in the heap in a node number order, in a string separated with
        the white space (automatically printed with built-in function)
        There will be no “error case” such as overflow, underflow.
*/
void task_6(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 6]" << endl;
    try
    {
        PriorityQueue pq;
        for (int i = 0; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0)
            {
                int input_value = instr_seq.getInstruction(i).getValue();

                /* BEGIN_YOUR_CODE*/
                if (!pq.insert(input_value, input_value)) {
                    fout << "Error"; // NOTE: Check if I need to check if pq is full
                    return;
                }
                /* END_YOUR_CODE */
            }
            else if (command.compare("removeMax") == 0)
            {
                /* BEGIN_YOUR_CODE*/
                if (!pq.removeMax()) {
                    fout << "Empty" << " ";
                }
                /* END_YOUR_CODE */
            }
            else if (command.compare("isEmpty") == 0)
            {
                /* BEGIN_YOUR_CODE*/
                fout << (pq.empty() ? "True" : "False") << " ";
                /* END_YOUR_CODE */
            }
            else
            {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << pq.printPQ() << endl;
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}


#ifndef DOING_CTEST // SUBMIT: REMOVE THIS LINE
int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    const char *instr_seq;
    const char ** instr_seq2;
    int node_value;
    string result;
    InstructionSequence instr_seq_heap;

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
        instr_seq = argv[2];
        if (task_num == 4)
            instr_seq2 = (const char**)(argv+2);
        if (task_num >= 5)
            instr_seq_heap.parseInstructions(argv[2]);
    }

    // Running the task(s)
    const char** arrs = const_cast<const char**>(TASK_4_DEFAULT_ARGUMENT);
    switch (task_num) {
        case 1:
            task_1(fout, instr_seq);
            break;
        case 2:
            task_2(fout, instr_seq);
            break;
        case 3:
            task_3(fout, instr_seq, argv[3]);
            break;
        case 4:
            task_4(fout, instr_seq2);
            break;
        case 5:
            task_5(fout, instr_seq_heap);
            break;
        case 6:
            task_6(fout, instr_seq_heap);
            break;
        case 0:
            task_1(fout, "1");
            task_1(fout, "2");
            task_2(fout, TASK_2_DEFAULT_ARGUMENT);
            task_3(fout, TASK_3_DEFAULT_ARGUMENT, TASK_3_DEFAULT_ARGUMENT_2);
            task_4(fout, arrs);

            instr_seq_heap.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq_heap);

            instr_seq_heap.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq_heap);
            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
#endif // SUBMIT: REMOVE THIS LINE