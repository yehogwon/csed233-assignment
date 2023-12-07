#include "test.h"
#include "pa4.cpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <string>
#include <fstream>
#include <map>

#define PA_ID 4

int main(int argc, char **argv) {
    std::vector<std::string> &&init_info = init_test(PA_ID, argc, argv);
    if (init_info.size() == 0) return -1;

    std::string test_name, prefix, answer_path;
    test_name = init_info[0];
    prefix = init_info[1];
    answer_path = init_info[2];
    std::ifstream answer_in(answer_path);

    std::map<std::string, function_1_args<InstructionSequence&>> test_functions = {
        {"Task1", task_1},
        {"Task2", task_2},
        {"Task3", task_3},
        {"Task4", task_4},
        {"Task5", task_5},
        {"Task6", task_6}, 
        {"Task7", task_7}
    };

    InstructionSequence instruction_sequence;
    return test_iteration_1_args<InstructionSequence&>(
        test_functions[test_name], 
        prefix, 
        answer_in, 
        [&instruction_sequence](const std::string &s) -> InstructionSequence& {
            instruction_sequence.parseInstructions(s.c_str());
            return instruction_sequence;
        }, 
        false, 
        false
    );
}
