#include "closed_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

int ClosedHashFunction::digits_sum(int key) {
    std::string str = std::to_string(key);
    int sum = 0;
    for (int i = 0; i < str.length(); i++) {
        sum += str[i] - '0';
    }
    return sum;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int ClosedHashFunction::closedhashing(int key, int attempt) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return (closedhashing1(key) + attempt * closedhashing2(key)) % this->index_size;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int ClosedHashFunction::closedhashing1(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return digits_sum(key) % this->index_size;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int ClosedHashFunction::closedhashing2(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return 1 + (key % (this->index_size - 1));
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
