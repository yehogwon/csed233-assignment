#ifndef __TEST_H__
#define __TEST_H__
#define DOING_CTEST

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <tuple>
#include <vector>
#include "utils.h"

#define CREATE_FILE_STREAMS \
    std::string temp_file = "/tmp/pa.test." + random_string(10) + time_stamp(); \
    std::ofstream temp_out(temp_file); \
    std::ifstream temp_in(temp_file);

#define GET_FILE_STREAM_CONTENT(x) \
    std::string x = "", line; \
    while (std::getline(temp_in, line)) { strip(line); x += line; } \
    strip(x);

#define CLOSE_FILE_STREAMS \
    temp_out.close(); \
    temp_in.close(); \
    std::remove(temp_file.c_str());

using function_no_args = void (*)(std::ofstream&);

template <typename... Types>
using function_args = std::function<void(std::ofstream&, Types...)>;

const char *CASE_SEP = "**** ****";

std::vector<std::string> init_test(int pa_id, int argc, char **argv) {
    // If successful, returns {test_name, prefix, answer_path}
    if (!(argc == 2 || argc == 3)) { // invalid arguments (requires test name)
        std::cout << "Invalid arguments" << std::endl;
        std::cout << "Usage: ./pa" << pa_id << ".test.out <test_name>" << std::endl;
        std::cout << "Or" << std::endl;
        std::cout << "Usage: ./pa" << pa_id << ".test.out <test_name> <answer_dir_path>" << std::endl;
        return {};
    }
    
    srand(time(NULL) * getpid());

    std::string test_name = argv[1];
    std::string test_name_lower = test_name;
    std::transform(test_name_lower.begin(), test_name_lower.end(), test_name_lower.begin(), ::tolower);
    std::string prefix = "[" + test_name + "]";
    prefix.insert(5, " ");

    std::string data_path = argc == 2 ? "data/" : std::string(argv[2]);
    std::string answer_path = data_path + test_name_lower + ".txt";
    
    if (access(answer_path.c_str(), F_OK) == -1) {
        std::cout << "Answer file does not exist" << std::endl;
        return {};
    }
    return {test_name, prefix, answer_path};
}

std::string identity_string(const std::string &s) {
    return s;
}

const char* identity_cstr(const std::string &s) {
    return s.c_str();
}

bool test_no_args(function_no_args fn, const std::string &expected_output) {
    CREATE_FILE_STREAMS
    fn(temp_out);
    GET_FILE_STREAM_CONTENT(full_content)
    CLOSE_FILE_STREAMS
    std::cout << "GOT: " << full_content << std::endl;
    return full_content == expected_output;
}

int test_iteration_0_args(const function_no_args fn, const std::string &prefix, std::ifstream &answer_in) {
    std::string answer;
    std::getline(answer_in, answer);
    answer_in.close();
    answer = prefix + answer;
    return !test_no_args(fn, answer);
}

int _getlines(std::ifstream &in, std::string *lines, int n_lines) {
    std::string line;
    for (int i = 0; i < n_lines; i++) {
        if (!std::getline(in, line)) return i;
        strip(line);
        lines[i] = line;
    }
    return n_lines;
}

template <typename... Types>
bool test_args(function_args<Types...> fn, Types... args, const std::string &answer) {
    CREATE_FILE_STREAMS
    fn(temp_out, args...);
    GET_FILE_STREAM_CONTENT(full_content)
    CLOSE_FILE_STREAMS
    std::cout << "GOT: " << full_content << std::endl;
    return full_content == answer;
}

template <typename... Types>
int test_iteration_args(
        const function_args<Types...> fn, 
        const std::string &prefix, std::ifstream &answer_in, 
        function_of_str<Types>... parse_inputs_fn,
        const bool nothing_for_empty=false
    ) {
    constexpr int n_inputs = sizeof...(Types);
    std::string inputs[n_inputs], answer, tmp;
    
    while (_getlines(answer_in, inputs, n_inputs) == n_inputs) {
        answer = "";
        while (std::getline(answer_in, tmp) && tmp != CASE_SEP) {
            strip(tmp);
            answer += prefix + tmp;
        }
        if (nothing_for_empty && answer == prefix) answer = ""; // If the answer is the empty string, follow the nothing_for_empty flag
        
        std::vector<std::variant<std::string, Types...>> test_args;
        apply_vector(test_args, parse_inputs_fn...);
        
        std::cout << "Testing: {";
        for (int i = 0; i < n_inputs; i++) {
            std::cout << inputs[i];
            if (i < n_inputs - 1) std::cout << ",";
        }
        std::cout << "} -> " << answer << std::endl;

        test_args.push_back(answer);
        unpack_caller<n_inputs + 1, function_args<Types...>, std::variant<std::string, Types...>> caller;
        if (!caller(fn, test_args)) {
        // if (!test_args<Types...>(fn, parsed_inputs, answer)) {
            std::cout << "Failed..." << std::endl;
            return 1;
        }
    }
    return 0;
}

#endif // __TEST_H__