/*
    Programming Assignment #3
*/
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#include "utils.h"
#include "sort.h"
#include "tree.h"
#include "bst.h"
#include "avl.h"
#include "open_hash_function.h"
#include "open_hash_table.h"
#include "closed_hash_function.h"
#include "closed_hash_table.h"

using namespace std;


/*
    [Task 1] insertion sort

    Description:
        Implement a function that sorts a given array using the insertion sort algorithm in ascending order. 
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::insertionSort function

    Input:
        ('insertion',integer): insert integer into the array
        ('insertionSort',NULL): sort the array using selection sort algorithm

    Output:
        Every value in the array for each sorting step including the initial step, 
        string separated with the white space (please use built-in function to print the array).
        You don’t need to consider exceptional cases such as overflow or an empty array. We will not test such cases.

*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 1]" << endl;
  try {
    sortAlg sort;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("insertion") == 0) {
        sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
        sort.arr_size++;
      } else if (command.compare("insertionSort") == 0) {
        sort.printArray(fout);
        sort.insertionSort(fout);
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 2] merge sort

    Description:
        Implement a function that sorts a given array using the merge sort
        algorithm in ascending order using non-recursive merge sort.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::mergeSort function
        TODO: Implement sortAlg::merge function

    Input:
        ('insertion',integer): insert integer into the array
        ('mergeSort',NULL): sort the array using merge sort algorithm

    Output:
        Every value in the array for each sorting step including the initial
   step, string separated with the white space (please use built-in function to
   print the array). You don’t need to consider exceptional cases such as
   overflow or an empty array. We will not test such cases.
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 2]" << endl;
  try {
    sortAlg sort;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("insertion") == 0) {
        sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
        sort.arr_size++;
      } else if (command.compare("mergeSort") == 0) {
        sort.printArray(fout);
        sort.mergeSort(fout, 0, sort.arr_size - 1);
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 3] BST insertion / deletion / FindNthMinimum

    Description:
        Implement a function that inserts and deletes an element into a BST and finds the N-th minimum value.
        You can modify bst.cpp and bst.h files for this problem.

        TODO: Implementation BinarySearchTree::insertion function
        TODO: Implementation BinarySearchTree::deletion function

    Input of BinearySearchTree::insertion
        Key of the element to be inserted.

    Output of BinearySearchTree::insertion
        Return the -1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    Input of BinearySearchTree::deletion
        Key of the element to be deleted.

    Output of BinearySearchTree::deletion
        Return the -1 if the key does not exist in the tree, 0 otherwise.
        (If the key does not exist, do not delete any element)

    Input of BinearySearchTree::findNthMinimum
        Key of the N-th minimum value to be found.

    Output of BinearySearchTree::findNthMinimum
        Return the -1 if there if no such N-th minimum value, N-th minimum value otherwise.

    task_3 prints
        the return for *each* insertion/deletion/NthMinimum value
        the return for N-th minimum value
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 3]" << endl;
    try {
        BinarySearchTree tree;
        int ret;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0) {
                ret = tree.insertion(key);
                fout << ret << endl;
            } else if (command.compare("deletion") == 0) {
                ret = tree.deletion(key);
                fout << ret << endl;
            } else if(command.compare("findNthMinimum") == 0){
                ret = tree.findNthMinimum(key);
                fout << ret << endl;
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << tree.preOrder() << endl;
        fout << tree.inOrder() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 4] AVL tree insertion / deletion

    Description:
        Implement a function that inserts and deletes an element into a AVL tree.
        The insertion and deletion might cause the AVL tree to violate its properties (imbalance). 
        Your code should be able to resolve the various imbalance type (LL, LR, RL, RR) of the AVL tree. 
        You can modify avl.cpp and avl.h files for this problem. 

        TODO: Implementation AVLTree::insertion function
        TODO: Implementation AVLTree::deletion function

        Hint : suggest you to call 'insertion' and 'deletion' function in BinarySearchTree class 

    Input of AVLTree::insertion
        Key of the element to be inserted.

    Output of AVLTree::insertion
        Return -1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    Input of AVLTree::deletion function
        Key of the element to  deleted

    Output of AVLTree::deletion
        Return -1 if the key does not exist in the tree, 0 otherwise.
        (If the key does not exist, do not delete any element)

    task_4 prints
        the return for *each* insertion/deletion and
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 4]" << endl;
    try {
        AVLTree tree;
        string result;
        // bool ret;
    for (int i = 0; i < instr_seq.getLength(); i++) {
        string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0) {
                result = tree.insertion(key);
                fout << result << endl;
            } else if (command.compare("deletion") == 0) {
                result = tree.deletion(key);
                fout << result << endl;
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << tree.preOrder() << endl;
        fout << tree.inOrder() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 5] Open hash table

    Description:
        Implement an open hash table with division-method. 
        This hash table is used with integer keys and hashing into a table of size M.
        Every component of the key is calculates as modulo as described in our Lecture Note. 
        This hash table uses a singly linked list as a collision handling method. You don’t need to consider deletion, the maximum length of the linked list and multiple insertions of the same key.
        You can modify open_hash_function.cpp, open_hash_table.cpp, open_hash_function.h and open_hash_table.h files for this problem.

        TODO: Implementation OpenHashFunction::openhashing and OpenHashFunction::insert functions


    Input: Two commands (The order is always 'M', and 'insertion')
      - ('M', integer): The size of a key
      - ('insertion', integer): A key to be hashed (in decimal)

    Output: For each slot of the hash table, print out
      - the linked list, if the state of the slot is occupied
      - the state, if the state of the slot is empty
*/

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 5]" << endl;
    try {
        int M;
        OpenHashFunction *hf;
        OpenHashTable *ht;

        if (instr_seq.getLength() < 2 ||
            instr_seq.getInstruction(0).getCommand().compare("M") != 0 ){
            cerr << "Invalid starting commands" << endl;
            exit(-1);
        }

        M = instr_seq.getInstruction(0).getValue();
        hf = new OpenHashFunction(M);
        ht = new OpenHashTable(M, hf);

        for (int i = 1; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0) {
                ht->insert(key);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }

        ht->print_table(fout);

        delete ht;
        delete hf;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 6] Closed hash table

    Description:
        Implement insertion of a closed hash table with rehashing implementation. 
        This hash table is used with integer keys and hashing into a table of size M.
        This hash table uses double hashing as a collision handling method. 
        The index of the key k  after i-th collision, h_i (k), is:

        h_i (k)=(h_1 (k)+ih_2 (k)) mod M 

        Where  h_1 (k) is the digital-folding method. 
        Every component of the key is folded with a size of 1(digit) and calculates their sum as described in our Lecture Note.  h_2 (k) is:

        h_2 (k)=1+(k mod (M-1))

        Hash table consists of 0 ~ (M-1) indices and you need to implement additional list named ‘F’ to contain integers that could not get into the hash table. 
        You don’t need to consider deletion or multiple insertions of the same key. 
        You can modify closed_hash_function.cpp, closed_hash_table.cpp, closed_hash_function.h and closed_hash_table.h files for this problem.

        TODO: Implementation ClosedHashFunction::insert, ClosedHashFunction::closedhashing, ClosedHashFunction::closedhashing1, and ClosedHashFunction::closedhashing2 functions


    Input: A sequence of commands
      - ('M', integer): The size of a key
                        (The first command is always 'n')
      - ('insertion', integer): Insert integer into the hash table

    Output: For each slot of the hash table, print out
      - the value if the state of the slot is occupied
      - the state if the state of the slot is empty or deleted
      - 'F: ' and its elements. If ‘F’ is empty, print empty.
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 6]" << endl;
    try {
        int M;
        ClosedHashFunction *hf;
        ClosedHashTable *ht;
        

        if (instr_seq.getLength() < 2 ||
            instr_seq.getInstruction(0).getCommand().compare("M") != 0) {
            cerr << "Invalid starting commands" << endl;
            exit(-1);
        }

        M = instr_seq.getInstruction(0).getValue();
        hf = new ClosedHashFunction(M);
        ht = new ClosedHashTable(M, hf);
        
        for (int i = 1; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0) {
                ht->insert(key);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }

        ht->print_table(fout);

        delete ht;
        delete hf;
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
        }
        catch (const char *e) {
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
            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
#endif // SUBMIT: REMOVE THIS LINE