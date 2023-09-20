#define DOING_CTEST
#include "pa1.cpp"

#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) { // invalid arguments (requires test name)
        std::cout << "Invalid arguments" << std::endl;
        std::cout << "Usage: ./pa1.test.out <test_name>" << std::endl;
        return -1;
    }

    std::string test_name = argv[1];
    
    std::string temp_file = "/tmp/pa1.test." + std::to_string(std::rand());
    std::ofstream temp_out(temp_file);

    if (test_name == "Task1") {
        task_1(temp_out);
        temp_out.close();

        std::ifstream temp_in(temp_file);
        std::string full_content = "", line;
        while (std::getline(temp_in, line)) full_content += line;
        std::cout << full_content << std::endl;

        return full_content == "[Task 1]4\n";
    } else if (test_name == "Task2") {
        task_2(temp_out);
        temp_out.close();

        std::ifstream temp_in(temp_file);
        std::string full_content = "", line;
        while (std::getline(temp_in, line)) full_content += line;
        std::cout << full_content << std::endl;

        return full_content == "[Task 2]2\n";
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
