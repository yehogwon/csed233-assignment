#define DOING_CTEST
#include "pa1.cpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <unistd.h>

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
        return !std::isspace(ch);
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
    std::string temp_file = "/tmp/pa1.test." + random_string(10);
    std::ofstream temp_out(temp_file);
    fn(temp_out);
    temp_out.close();

    std::ifstream temp_in(temp_file);
    std::string full_content = "", line;
    while (std::getline(temp_in, line)) full_content += line;
    strip(full_content);
    temp_in.close();

    std::remove(temp_file.c_str());
    return full_content == expected_output;
}

template <typename T>
bool test_1_args(const std::pair<T, std::string> &test_case) {
    return false;
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
        return 1; // to be implemented
    } else if (test_name == "Task4") {
        return 1; // to be implemented
    } else if (test_name == "Task5") {
        return 1; // to be implemented
    } else if (test_name == "Task6") {
        return 1; // to be implemented
    } else {
        std::cout << "Invalid test name" << std::endl;
        return -2; // invalid test name
    }
}
