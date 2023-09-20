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

    if (test_name == "Task1") {
        return 1; // to be implemented
    } else if (test_name == "Task2") {
        return 1; // to be implemented
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
