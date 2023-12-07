#include <iostream>

using namespace std;

class Instruction {
public:
  void setCommand(string cmd);
  void setValue(int val);
  void setValueStr(string val);

  string getCommand();
  int getValue();
  string getValueStr();

private:
  string command;
  string value_str;
  int value;
};

class InstructionSequence {
public:
  InstructionSequence();
  ~InstructionSequence();

  int getLength();
  Instruction &getInstruction(int index);

  void parseInstructions(const char *arg);
  void printInstructions();

private:
  Instruction *instructions;
  int length;
};

const char *const TASK_1_DEFAULT_ARGUMENT = "[('A','B'), ('B','C'), ('A','C')]";
const char *const TASK_2_DEFAULT_ARGUMENT = "[('A','B'), ('B','C'), ('A','C')]";
const char *const TASK_3_DEFAULT_ARGUMENT =
    "[('A','B'), ('B','C'), ('C','A'), ('D','B'), ('D','E'), ('E','G'), "
    "('F','E'), ('G','F')]";
const char *const TASK_4_DEFAULT_ARGUMENT = "[('A','B'), ('B','C'), ('C','A')]";
const char *const TASK_5_DEFAULT_ARGUMENT =
    "[('A-B',10),('A-C',3),('B-D',5),('C-B',2),('C-E',15),('A-D',20),('D-E',11)"
    ",('A',11)]";
const char *const TASK_6_DEFAULT_ARGUMENT =
    "[('A-B', 3), ('A-C', 1), ('B-C', 4), ('B-D', 1), ('C-D', 2), ('D-E', 5), "
    "('MST', NULL)]";
const char *const TASK_7_DEFAULT_ARGUMENT =
    "[('A-B', 3), ('A-C', 1), ('B-C', 4), ('B-D', 1), ('C-D', 2), ('D-E', 5), "
    "('PATH-A-E', NULL)]";
