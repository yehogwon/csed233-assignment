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
        std::string answer;
        std::getline(answer_in, answer);
        answer_in.close();
        
        answer = prefix + answer;
        return !test_no_args(no_args_functions[test_name], answer);
    } else if (test_name == "Task3" || test_name == "Task5" || test_name == "Task6") {
        std::ifstream answer_in(answer_path);
        std::string input, answer, tmp;

        while (std::getline(answer_in, input)) {
            answer = "";
            while (std::getline(answer_in, tmp) && tmp != CASE_SEP) {
                strip(tmp);
                answer += prefix + tmp;
            }
            if (test_name == "Task6" && answer == prefix) answer = ""; // If the answer is the empty string, Task 6 does not print anything. 
            strip(input);
            std::pair<InstructionSequence*, std::string> test_case = {
                ParseInstructions(input.c_str()), 
                answer
            };
            std::cout << "Testing: " << input << " -> " << test_case.second << std::endl;
            if (!test_1_args<InstructionSequence*>(one_args_functions[test_name], test_case)) {
                std::cout << "Failed..." << std::endl;
                return 1;
            }
        }
        return 0;
    } else if (test_name == "Task4") {
        std::ifstream answer_in(answer_path);
        std::string input, answer, tmp;

        while (std::getline(answer_in, input)) {
            answer = "";
            while (std::getline(answer_in, tmp) && tmp != CASE_SEP) {
                strip(tmp);
                answer += prefix + tmp;
            }
            strip(input);
            std::pair<std::string, std::string> test_case = {
                input, 
                answer
            };
            std::cout << "Testing: " << input << " -> " << test_case.second << std::endl;
            if (!test_1_args<std::string>(one_args_functions_str[test_name], test_case)) {
                std::cout << "Failed..." << std::endl;
                return 1;
            }
        }
        return 0;
    } else {
        std::cout << "Invalid test name" << std::endl;
        return -2; // invalid test name
    }
}
