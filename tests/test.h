#ifndef __TEST_H__
#define __TEST_H__
#define DOING_CTEST

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <functional>
#include <map>

#define TMP_DIR "/tmp"
#define TMP_FILE_PREFIX "__csed233.pa.test."
#define TMP_FILE_VAR __tmp_file
#define TMP_FILE_OUT_STREAM __tmp_out
#define TMP_FILE_IN_STREAM __tmp_in

#define CREATE_FUNCTION_RESULT(F, ...) \
    std::string TMP_FILE_VAR = TMP_DIR "/" TMP_FILE_PREFIX + random_string(10) + time_stamp(); \
    std::ofstream TMP_FILE_OUT_STREAM(TMP_FILE_VAR); \
    F(TMP_FILE_OUT_STREAM, ##__VA_ARGS__); \
    TMP_FILE_OUT_STREAM.close();

#define GET_FUNCTION_RESULT(X) \
    std::ifstream TMP_FILE_IN_STREAM(TMP_FILE_VAR); \
    std::string X, line; \
    while (std::getline(TMP_FILE_IN_STREAM, line)) { strip(line); X += line; } \
    strip(X); \
    TMP_FILE_IN_STREAM.close();

#define REMOVE_TMP_FILE \
    std::remove(TMP_FILE_VAR.c_str());

using function_no_args = void (*)(std::ofstream&);

template <typename T>
using function_1_args = std::function<void(std::ofstream&, T)>;

template <typename T, typename U>
using function_2_args = std::function<void(std::ofstream&, T, U)>;

template <typename T>
using function_parse_input = std::function<T(const std::string&)>;

const char *SYMBOLS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int SYMBOLS_LEN = 62;

const char *CASE_SEP = "**** ****";

std::vector<std::string> init_test(int pa_id, int argc, char **argv) {
    // If successful, returns {test_name, prefix, answer_path}
    if (!(argc == 2 || argc == 3 || argc == 4)) { // invalid arguments (requires test name)
        std::cout << "Invalid arguments" << std::endl;
        std::cout << "Usage: ./pa" << pa_id << ".test.out <test_name>" << std::endl;
        std::cout << "Or" << std::endl;
        std::cout << "Usage: ./pa" << pa_id << ".test.out <test_name> <suffix>" << std::endl;
        std::cout << "Or" << std::endl;
        std::cout << "Usage: ./pa" << pa_id << ".test.out <test_name> <suffix> <answer_dir_path>" << std::endl;
        std::cout << "By default, <suffix> is empty and <answer_dir_path> is \"data/\"" << std::endl;
        std::cout << "If suffix is non-empty, the answer file will be <answer_dir_path>/<lower_test_name>.<suffix>.txt" << std::endl;
        return {};
    }
    
    srand(time(NULL) * getpid());

    std::string test_name = argv[1];
    std::string test_name_lower = test_name;
    std::transform(test_name_lower.begin(), test_name_lower.end(), test_name_lower.begin(), ::tolower);
    std::string prefix = "[" + test_name + "]";
    prefix.insert(5, " ");

    std::string suffix = argc == 3 ? std::string(argv[2]) : "";
    std::string suffix_lower = suffix;
    std::transform(suffix_lower.begin(), suffix_lower.end(), suffix_lower.begin(), ::tolower);

    std::string answer_file_name = test_name_lower + (suffix_lower.size() > 0 ? "." : "") + suffix_lower + ".txt";
    std::string data_path = argc != 4 ? "data/" : std::string(argv[3]);
    std::string answer_path = data_path + answer_file_name;
    
    if (access(answer_path.c_str(), F_OK) == -1) {
        std::cout << "Answer file does not exist: " << answer_path << std::endl;
        return {};
    }
    return {test_name, prefix, answer_path};
}

std::string time_stamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string ts = std::to_string(ltm->tm_year + 1900) + std::to_string(ltm->tm_mon + 1) + std::to_string(ltm->tm_mday) + std::to_string(ltm->tm_hour) + std::to_string(ltm->tm_min) + std::to_string(ltm->tm_sec);
    return ts;
}

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

std::string identity_string(const std::string &s) {
    return s;
}

const char* identity_cstr(const std::string &s) {
    return s.c_str();
}

bool test_no_args(function_no_args fn, const std::string &expected_output) {
    CREATE_FUNCTION_RESULT(fn)
    GET_FUNCTION_RESULT(full_content)
    REMOVE_TMP_FILE
    std::cout << "GOT: " << full_content << std::endl;
    return full_content == expected_output;
}

template <typename T>
bool test_1_args(function_1_args<T> fn, const std::pair<T, std::string> &test_case) {
    CREATE_FUNCTION_RESULT(fn, test_case.first)
    GET_FUNCTION_RESULT(full_content)
    REMOVE_TMP_FILE
    std::cout << "GOT: " << full_content << std::endl;
    return full_content == test_case.second;
}

template <typename T, typename U>
bool test_2_args(function_2_args<T, U> fn, const std::pair<std::pair<T, U>, std::string> &test_case) {
    CREATE_FUNCTION_RESULT(fn, test_case.first.first, test_case.first.second)
    GET_FUNCTION_RESULT(full_content)
    REMOVE_TMP_FILE
    std::cout << "GOT: " << full_content << std::endl;
    return full_content == test_case.second;
}

int test_iteration_0_args(const function_no_args fn, const std::string &prefix, std::ifstream &answer_in) {
    std::string answer;
    std::getline(answer_in, answer);
    answer_in.close();
    answer = prefix + answer;
    return !test_no_args(fn, answer);
}

template <typename T>
int test_iteration_1_args(const function_1_args<T> fn, const std::string &prefix, std::ifstream &answer_in, function_parse_input<T> parse_input, const bool nothing_for_empty=false, const bool prefix_every_line=true) {
    std::string input, answer, tmp;
    while (std::getline(answer_in, input)) {
        answer = "";
        while (std::getline(answer_in, tmp) && tmp != CASE_SEP) {
            strip(tmp);
            if (prefix_every_line) answer += prefix;
            answer += tmp;
        }
        if (!prefix_every_line) answer = prefix + answer;
        if (nothing_for_empty && answer == prefix) answer = ""; // `nothing_for_empty` is True when the task does not print even [Task #] when that is the only line to print. 
        strip(input);
        std::pair<T, std::string> test_case = {
            parse_input(input),
            answer
        };
        std::cout << "Testing: " << input << " -> " << test_case.second << std::endl;
        if (!test_1_args<T>(fn, test_case)) {
            std::cout << "Failed..." << std::endl;
            return 1;
        }
    }
    return 0;
}

// NOTE: Generalize this function to take any number of arguments. What about using variadic templates?
template <typename T, typename U>
int test_iteration_2_args(const function_2_args<T, U> fn, const std::string &prefix, std::ifstream &answer_in, function_parse_input<T> parse_input1, function_parse_input<U> parse_input2, const bool nothing_for_empty=false) {
    std::string input, input1, input2, answer, tmp;
    while (std::getline(answer_in, input)) {
        // split input with space and assign input1 and input2
        std::istringstream iss(input);
        iss >> input1 >> input2;

        answer = "";
        while (std::getline(answer_in, tmp) && tmp != CASE_SEP) {
            strip(tmp);
            answer += prefix + tmp;
        }
        if (nothing_for_empty && answer == prefix) answer = ""; // If the answer is the empty string, Task 6 does not print anything. 
        strip(input1); strip(input2);
        std::pair<std::pair<T, U>, std::string> test_case = {
            {
                parse_input1(input1), 
                parse_input2(input2)
            },
            answer
        };
        std::cout << "Testing: {" << input1 << "," << input2 << "} -> " << test_case.second << std::endl;
        if (!test_2_args<T, U>(fn, test_case)) {
            std::cout << "Failed..." << std::endl;
            return 1;
        }
    }
    return 0;
}

#endif // __TEST_H__