#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* 
    [Task 1] Choose the TIGHT bound of the following arraySum function
    
    *Fibonacci*
        Input
        - int n: An integer n >= 1
        Output
        - int: The n-th Fibonacci number, which is an integer

	int fibonacci(int n){
    if (n==1) return 1;
    if (n==2) return 1; 

    return fibonacci(n-1) + fibonacci(n-2);
  }
	}


    Choices
        1: O( log(n) )
        2: O( n log(n) )
        3: O( n^2 )
        4: O( 2^n )
*/
void task_1(ofstream &fout) {
    int answer = 4;  // TODO: Change to your answer

    fout << "[Task 1]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 2] Choose the time complexity of the following fibonacci

    *primeSearch*
        Input
        - int n: An integer n >= 1
        Output
        - int: The n-th Fibonacci number, which is an integer

    int fibonacci2(int n){
      int f[n+1];
      f[1] = 1;
      f[2] = 1;

      for (int i=3; i<=n; i++){
        f[i] = f[i-1] + f[i-2];
      }
      return f[n];
    }


    Choices
        1: O( 1 )
        2: O( n )
        3: O( log(n) )
        4: O( n^2 )
*/
void task_2(ofstream &fout) {
    int answer = 2;  // TODO: Change to your answer

    fout << "[Task 2]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or delete an integer into the list.
        An user can insert an element in ascending order
        or delete an element at the specific index.
        If the specified index is out of range of the given list, print “error”.

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,integer value): insert integer value at the appropriate
   position in the list, while ensuring that the elements within the array are
   always in ascending order. index indicates zero-based index.
        - (‘delete’,index): delete an element at the index in the list. index
   indicates zero-based index.

    Output:
        - An array after insertion/deletion in a string separated with the
   spacebar
        - “error” if the index is out of range
*/

void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int *arr = new int[instr_seq->length], length = 0;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int val = instr_seq->instructions[i].value;
    if (command.compare("insert") == 0) {
      /* TODO: Implement */
      if (length == 0) {
        arr[0] = val;
        length++;
      } else {
        int idx = 0;
        while (idx < length && arr[idx] < val) {
          idx++;
        }
        for (int j = length; j > idx; j--) {
          arr[j] = arr[j - 1];
        }
        arr[idx] = val;
        length++;
      }
    } else if (command.compare("delete") == 0) {
      /* TODO: Implement */
      if (length == 0) {
        answer = "error";
        break;
      }
      int idx = val;
      if (idx >= length) {
        answer = "error";
        break;
      }
      for (int j = idx; j < length - 1; j++) {
        arr[j] = arr[j + 1];
      }
      length--;
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if (answer != "error")
    for (int i = 0; i < length; i++)
      answer += to_string(arr[i]) + " "; // trainling spaces do not matter

  delete[] arr;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 3]" << endl;
  fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        b.	Implement a stack and a function MatchingParentheses that returns the 
        matching correctness of arithmetic expression when the expression is given 
        and using your stack implementation

    Input:
        An arithmetic expression consists of at least one group of symbols (Parentheses, Braces, Brackets). 
        Please ignore the other input cases 
      Example ) 
      1. ({[]})
      2. (((
      3. []]]}()

    Output:
        -	True : If the given expression satisfies the pair matching  
        -	False : If the given expression doesn’t satisfy the pair matching 

*/

/* DO NOT CHANGE */
struct stack {
  char value;
  stack* next;
};

struct Top {
  int count; 
  struct stack* head;
};

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
char pop(Top* top){
    char val = top->head->value;
    stack *tmp = top->head;
    top->head = top->head->next;
    delete tmp;
    top->count--;
    return val;
}


void push(char exp, Top* top){
  stack *new_node = new stack;
  new_node->value = exp;
  new_node->next = top->head;
  top->head = new_node;
  top->count++;
}

void delete_top(Top *top) {
  while (top->count > 0) pop(top);
  delete top;
}

bool MatchingParentheses(string ari_exp) { 
  Top *top = new Top;
  top->count = 0;
  top->head = nullptr;
  for (char c : ari_exp) {
    if (c == '(' || c == '{' || c == '[') { // open
      push(c, top);
    } else if (c == ')' || c == '}' || c == ']') { // close
      if (top->count == 0) { // got close, but nothing opened
        delete_top(top);
        return false;
      } else {
        char top_char = pop(top);
        if (c == ')' && top_char != '(' || c == '}' && top_char != '{' || c == ']' && top_char != '[') return false;
        // return false if the close does not match the most recent open
      }
    }
  }

  bool ret = top->count == 0;
  delete_top(top);
  return ret;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////




void task_4(ofstream &fout, string expression) {
  string answer;

  if (MatchingParentheses(expression))
    answer = "True";
  else 
    answer = "False";
 

  fout << "[Task 4]" << endl;
  fout << answer << endl;
}

/*
    [Task 5] Queue

    Description:
        Implement a function that shows results of series of commands for a queue. 

    Command:
        -	(‘e’,int): enqueue integer into the current queue.
        -	(‘d’,NULL): dequeue one element from the current queue. If dequeue from the empty queue, print only ‘error’.
        -	(‘show’,NULL): show the value of the current queue. If the queue is empty, print ‘empty’.
        -	(‘size’,NULL): show the number of the elements of the current queue.
        -	(‘isEmpty’,NULL): show whether the current queue is empty or not. If the queue is empty, print ‘F’. Otherwise, print ‘T’.
        -	(‘clear’,NULL): dequeue all elements from the current queue.

    Caution:
        -	There should be a space between two outputs. 
*/

void task_5(ofstream &fout, InstructionSequence *instr_seq) {
    string answer;
    string queue;
    int size = 0;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    int head = 0; // the index of the first digit of the heading item
    for (int i = 0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        int value = instr_seq->instructions[i].value;

        if (command.compare("e") == 0) {
          queue += to_string(value) + " ";
          size++;
        } else if (command.compare("d") == 0) {
          if (size == 0) {
            answer = "error";
            break;
          }
          while (queue[head++] != ' ');
          size--;
        } else if (command.compare("show") == 0) {
          if (size == 0) {
            answer += "empty";
            break;
          }
          int start_ = head;
          int count = 0;
          while (true) {
            answer += queue[start_++];
            if (queue[start_] == ' ' && ++count >= size) break;
          }
          answer += " ";
        } else if (command.compare("size") == 0) {
          answer += to_string(size) + " ";
        } else if (command.compare("isEmpty") == 0) {
            answer += size == 0 ? "T" : "F";
            answer += " ";
        } else if (command.compare("clear") == 0) {
            queue = "";
            size = 0;
            head = 0;
        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 5]" << endl;
  fout << answer << endl;
}

/*
    [Task 6] Circular Queue

    a. Implement a function that shows the values in a circular queue with a counter.
    If “e” is called for an already full queue or the “d” operation is called for an empty queue,
    there should be no changes to the queue. The maximum number of elements (n) in the queue is five.

    b. Input & Output
    Input:  Sequence of commands, which is one of the following,
    •	(‘e’, int): enqueue integer into the current queue
    •	(‘d’): dequeue from the current queue
    •	(‘show’): show the value of the current queue. If the queue is empty, print ‘empty’
    •	(‘num’): show the number of elements in circular queue.

    Output
    •	Values in the circular queue (mod size n = 5), from the front to the rear. String separated with the spacebar
    •	No pointer movement if dequeue applied on an empty queue or enqueue applied on a full queue

*/

void task_6(ofstream &fout, InstructionSequence *instr_seq) {
    string answer;
    int queue_size = 5;
    int arr[5] = {};

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int cnt = 0, front = 0, rear = 0;
    for (int i = 0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("e") == 0) {
            /* TODO: Implement */
            
        } else if (command.compare("d") == 0) {
            /* TODO: Implement */
           

        } else if (command.compare("size") == 0) {

          fout << "[Task 6]" << endl;
          fout << cnt << endl;

        } else if (command.compare("show")==0){
          /* TODO: Implement */
            
          fout << "[Task 6]" << endl;
          fout << answer << endl;
        }
        else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
}
#ifndef DOING_CTEST // FIRE: CLEAR THIS LINE (DO NOE REMOVE THIS LINE THOUGH)
int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence *instr_seq;
  string expression;

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
    if(task_num == 4)
      expression = argv[2];
    else{
      try {
        instr_seq = ParseInstructions(argv[2]);
      } catch (const char *e) {
        cerr << e << endl;
        return -1;
      }
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout);
    break;
  case 2:
    task_2(fout);
    break;
  case 3:
    task_3(fout, instr_seq);
    break;
  case 4:
    task_4(fout, expression);
    break;
  case 5:
    task_5(fout, instr_seq);
    break;
  case 6:
    task_6(fout, instr_seq);
    break;
  case 0:
    task_1(fout);

    task_2(fout);

    InstructionSequence *instr_seq_3;
    instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq_3);

    InstructionSequence *instr_seq_4;
    expression = TASK_4_DEFAULT_ARGUMENT;
    task_4(fout, expression);

    InstructionSequence *instr_seq_5;
    instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq_5);

    InstructionSequence *instr_seq_6;
    instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq_6);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
#endif // FIRE: CLEAR THIS LINE (DO NOE REMOVE THIS LINE THOUGH)
