#include "test.h"
#include "pa2.cpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

#define PA_ID 2

int main(int argc, char **argv) {
    std::vector<std::string> &&init_info = init_test(PA_ID, argc, argv);
    if (init_info.size() == 0) return -1;

    std::string test_name, prefix, answer_path;
    test_name = init_info[0];
    prefix = init_info[1];
    answer_path = init_info[2];
    std::ifstream answer_in(answer_path);

    std::map<std::string, function_1_args<const char*>> one_args_functions_cstr = {
        {"Task1", task_1},
        {"Task2", task_2},
    };

    std::map<std::string, function_2_args<const char*, const char*>> two_args_functions_cstrs = {
        {"Task3", task_3},
    };

    std::map<std::string, function_1_args<const char*[]>> one_args_functions_cstarr = {
        {"Task4", task_4},
    };

    std::map<std::string, function_1_args<InstructionSequence&>> one_args_functions_insts = {
        {"Task5", task_5},
        {"Task6", task_6},
    };
    
    if (test_name == "Task1" || test_name == "Task2") {
        return test_iteration_1_args(
            one_args_functions_cstr[test_name], 
            prefix, 
            answer_in, 
            identity_cstr
        );
    } else if (test_name == "Task3") {
        // NOTE: Implement automatic test for Task3
    } else if (test_name == "Task4") {
        // NOTE: Implement automatic test for Task4
    } else if (test_name == "Task5" || test_name == "Task6") {
        // NOTE: Implement automatic test for Task5 and Task6
    } else {
        std::cout << "Invalid test name" << std::endl;
        return -2; // invalid test name
    }
}
