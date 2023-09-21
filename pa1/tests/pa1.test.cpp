#define DOING_CTEST
#include "pa1.cpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <unistd.h>

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
    return full_content == expected_output;
}

template <typename T>
bool test_1_args(function_1_args<T> fn, const std::pair<T, std::string> &test_case) {
    CREATE_FILE_STREAMS
    fn(temp_out, test_case.first);
    GET_FILE_STREAM_CONTENT(full_content)
    CLOSE_FILE_STREAMS
    return full_content == test_case.second;
}

int main(int argc, char **argv) {
    if (argc != 2) { // invalid arguments (requires test name)
        std::cout << "Invalid arguments" << std::endl;
        std::cout << "Usage: ./pa1.test.out <test_name>" << std::endl;
        return -1;
    }

    srand(time(NULL) * getpid());
    std::string test_name = argv[1];
    
    if (test_name == "Task1") {
        return !test_no_args(task_1, "[Task 1]4");
    } else if (test_name == "Task2") {
        return !test_no_args(task_2, "[Task 2]2");
    } else if (test_name == "Task3") {
        std::vector<std::pair<const char*, std::string>> test_cases = {
            {"[('insert',2),('insert',1),('insert',3)]", "1 2 3"},
            {"[('insert',0),('insert',0),('insert',1)]", "0 0 1"},
            {"[('insert',0),('insert',1),('delete',0)]", "1"},
            {"[('insert',0),('delete',1)]", "error"},
            {"[('delete',0)]", "error"},
            {"[('insert',5),('insert',9),('delete',0),('insert',1),('insert',2)]", "1 2 9"}
        };
        
        for (const auto &test_case_ : test_cases) {
            std::pair<InstructionSequence*, std::string> test_case = {
                ParseInstructions(test_case_.first), 
                "[Task 3]" + test_case_.second
            };
            if (!test_1_args<InstructionSequence*>(task_3, test_case)) {
                std::cout << "FAIL on test case: " << test_case_.first << " -> " << test_case.second << std::endl;
                return 1;
            }
        }
        return 0;
    } else if (test_name == "Task4") {
        std::vector<std::pair<std::string, std::string>> test_cases = {
            {"[()]", "True"}, 
            {"()(()){[]}", "True"}, 
            {"((){[]}[({}())])", "True"}, 
            {"{", "False"}, 
            {"()({{}}]", "False"}
        };
        
        for (const auto &test_case_ : test_cases) {
            std::pair<std::string, std::string> test_case = {
                test_case_.first, 
                "[Task 4]" + test_case_.second
            };
            if (!test_1_args<std::string>(task_4, test_case)) {
                std::cout << "FAIL on test case: " << test_case_.first << " -> " << test_case.second << std::endl;
                return 1;
            }
        }
        return 0;
    } else if (test_name == "Task5") {
        return 1; // to be implemented
    } else if (test_name == "Task6") {
        return 1; // to be implemented
    } else {
        std::cout << "Invalid test name" << std::endl;
        return -2; // invalid test name
    }
}
