#include "test.h"
#include "pa1.cpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

#define PA_ID 1

int main(int argc, char **argv) {
    std::vector<std::string> &&init_info = init_test(PA_ID, argc, argv);
    if (init_info.size() == 0) return -1;

    std::string test_name, prefix, answer_path;
    test_name = init_info[0];
    prefix = init_info[1];
    answer_path = init_info[2];

    std::map<std::string, function_no_args> no_args_functions = {
        {"Task1", task_1},
        {"Task2", task_2},
    };

    std::map<std::string, function_args<InstructionSequence*>> one_args_functions = {
        {"Task3", task_3},
        {"Task5", task_5},
        {"Task6", task_6},
    };

    std::map<std::string, function_args<std::string>> one_args_functions_str = {
        {"Task4", task_4},
    };
    
    if (test_name == "Task1" || test_name == "Task2") {
        std::ifstream answer_in(answer_path);
        return test_iteration_0_args(
            no_args_functions[test_name], 
            prefix, 
            answer_in
        );
    } else if (test_name == "Task3" || test_name == "Task5" || test_name == "Task6") {
        std::ifstream answer_in(answer_path);
        test_iteration_args<InstructionSequence*>(
            one_args_functions[test_name], 
            prefix, 
            answer_in, 
            [](const std::string &str) -> InstructionSequence* {
                return ParseInstructions(str.c_str());
            }, 
            test_name == "Task5"
        );
    } else if (test_name == "Task4") {
        std::ifstream answer_in(answer_path);
        return test_iteration_args<std::string>(
            one_args_functions_str[test_name], 
            prefix, 
            answer_in, 
            identity_string, 
            false
        );
    } else {
        std::cout << "Invalid test name" << std::endl;
        return -2; // invalid test name
    }
}
