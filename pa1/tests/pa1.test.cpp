#include "test.h"
#include "pa1.cpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <map>

int main(int argc, char **argv) {
    if (!(argc == 2 || argc == 3)) { // invalid arguments (requires test name)
        std::cout << "Invalid arguments" << std::endl;
        std::cout << "Usage: ./pa1.test.out <test_name>" << std::endl;
        std::cout << "Or" << std::endl;
        std::cout << "Usage: ./pa1.test.out <test_name> <answer_dir_path>" << std::endl;
        return -1;
    }

    srand(time(NULL) * getpid());
    std::string test_name = argv[1];
    std::string test_name_lower = test_name;
    std::transform(test_name_lower.begin(), test_name_lower.end(), test_name_lower.begin(), ::tolower);
    std::string prefix = "[" + test_name + "]";
    prefix.insert(5, " ");

    std::string data_path = argc == 2 ? "data/" : std::string(argv[2]);
    std::string answer_path = data_path + test_name_lower + ".txt";

    std::map<std::string, function_no_args> no_args_functions = {
        {"Task1", task_1},
        {"Task2", task_2},
    };

    std::map<std::string, function_1_args<InstructionSequence*>> one_args_functions = {
        {"Task3", task_3},
        {"Task5", task_5},
        {"Task6", task_6},
    };

    std::map<std::string, function_1_args<std::string>> one_args_functions_str = {
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
        return test_iteration_1_args<InstructionSequence*>(
            one_args_functions[test_name], 
            prefix, 
            answer_in, 
            [](const std::string &str) -> InstructionSequence* {
                return ParseInstructions(str.c_str());
            }, 
            test_name == "Task6"
        );
    } else if (test_name == "Task4") {
        std::ifstream answer_in(answer_path);
        return test_iteration_1_args<std::string>(
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
