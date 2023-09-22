#define DOING_CTEST
#include "pa1.cpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <unistd.h>
#include <map>

#define CREATE_FILE_STREAMS \
    std::string temp_file = "/tmp/pa1.test." + random_string(10); \
    std::ofstream temp_out(temp_file); \
    std::ifstream temp_in(temp_file);

#define GET_FILE_STREAM_CONTENT(x) \
    std::string x = "", line; \
    while (std::getline(temp_in, line)) x += line; \
    strip(x);

#define CLOSE_FILE_STREAMS \
    temp_out.close(); \
    temp_in.close(); \
    std::remove(temp_file.c_str());

using function_no_args = void (*)(std::ofstream&);

template <typename T>
using function_1_args = void (*)(std::ofstream&, T);

const char *SYMBOLS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int SYMBOLS_LEN = 62;

std::string random_string(const int len) {
    std::string rstr;
    rstr.reserve(len);
    for (int i = 0; i < len; i++) rstr += SYMBOLS[std::rand() % SYMBOLS_LEN];
    return rstr;
}

inline void lstrip(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch) && ch != '\n';
    }));
}


inline void rstrip(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void strip(std::string &s) {
    lstrip(s);
    rstrip(s);
}

bool test_no_args(function_no_args fn, const std::string &expected_output) {
    CREATE_FILE_STREAMS
    fn(temp_out);
    GET_FILE_STREAM_CONTENT(full_content)
    CLOSE_FILE_STREAMS
    std::cout << "GOT: " << full_content << std::endl;
    return full_content == expected_output;
}

template <typename T>
bool test_1_args(function_1_args<T> fn, const std::pair<T, std::string> &test_case) {
    CREATE_FILE_STREAMS
    fn(temp_out, test_case.first);
    GET_FILE_STREAM_CONTENT(full_content)
    CLOSE_FILE_STREAMS
    std::cout << "GOT: " << full_content << std::endl;
    return full_content == test_case.second;
}

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
        std::string input, answer;

        while (std::getline(answer_in, input) && std::getline(answer_in, answer)) {
            strip(input);
            std::pair<InstructionSequence*, std::string> test_case = {
                ParseInstructions(input.c_str()), 
                prefix + answer
            };
            if (!test_1_args<InstructionSequence*>(one_args_functions[test_name], test_case)) {
                std::cout << "FAIL on test case: " << input << " -> " << test_case.second << std::endl;
                return 1;
            }
        }
        return 0;
    } else if (test_name == "Task4") {
        std::ifstream answer_in(answer_path);
        std::string input, answer;

        while (std::getline(answer_in, input) && std::getline(answer_in, answer)) {
            strip(input);
            std::pair<std::string, std::string> test_case = {
                input,
                prefix + answer
            };
            if (!test_1_args<std::string>(one_args_functions_str[test_name], test_case)) {
                std::cout << "FAIL on test case: " << input << " -> " << test_case.second << std::endl;
                return 1;
            }
        }
        return 0;
    } else {
        std::cout << "Invalid test name" << std::endl;
        return -2; // invalid test name
    }
}
