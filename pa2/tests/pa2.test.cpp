#include "test.h"
#include "pa2.cpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
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

    std::map<std::string, function_args<const char*>> one_args_functions_cstr = {
        {"Task1", task_1},
        {"Task2", task_2},
    };

    std::map<std::string, function_args<const char*, const char*>> two_args_functions_cstrs = {
        {"Task3", task_3},
    };

    std::map<std::string, function_args<const char*[]>> one_args_functions_cstarr = {
        {"Task4", task_4},
    };

    std::map<std::string, function_args<InstructionSequence&>> one_args_functions_insts = {
        {"Task5", task_5},
        {"Task6", task_6},
    };
    
    if (test_name == "Task1" || test_name == "Task2") {
        return test_iteration_args<const char*>(
            one_args_functions_cstr[test_name], 
            prefix, 
            answer_in, 
            identity_cstr
        );
    } else if (test_name == "Task3") {
        return test_iteration_args<const char*, const char*>(
            two_args_functions_cstrs[test_name],
            prefix,
            answer_in, 
            identity_cstr,
            identity_cstr
        );
    } else if (test_name == "Task4") {
        std::vector<char*> args;
        const char *parsed_argv[3];
        return test_iteration_args<const char**>(
            one_args_functions_cstarr[test_name], 
            prefix, 
            answer_in, 
            [&args, &parsed_argv](const std::string &s) -> const char** {
                std::istringstream iss(s);
                std::string token;
                while(iss >> token) {
                    char *arg = new char[token.size() + 1];
                    copy(token.begin(), token.end(), arg);
                    arg[token.size()] = '\0';
                    args.push_back(arg);
                }
                assert(args.size() == 3 && "Invalid number of arguments");
                parsed_argv[0] = args[0];
                parsed_argv[1] = args[1];
                parsed_argv[2] = args[2];
                return parsed_argv;
            }
        );
        for (char* arg : args) delete[] arg;
    } else if (test_name == "Task5" || test_name == "Task6") {
        InstructionSequence instruction_sequence;
        return test_iteration_args<InstructionSequence&>(
            one_args_functions_insts[test_name], 
            prefix, 
            answer_in, 
            [&instruction_sequence](const std::string &s) -> InstructionSequence& {
                instruction_sequence.parseInstructions(s.c_str());
                return instruction_sequence;
            }
        );
        return 0;
    } else {
        std::cout << "Invalid test name" << std::endl;
        return -2; // invalid test name
    }
}
