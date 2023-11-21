#include <iostream>
#include <fstream>
#include <string>
#include "open_hash_function.h"
#include "open_hash_table.h"

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

OpenHashTable::OpenHashTable(int table_size, OpenHashFunction *hf) : table_size(table_size) {
    this->hf = hf;
    table = new HashNode*[this->table_size];
    for(int i = 0; i < this->table_size; i++){
        table[i] = NULL;
    }
    this->states = new OpenTableState[this->table_size];

    for (int i = 0; i < this->table_size; ++i) {
            this->states[i] = OPEN_EMPTY;
    }

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

OpenHashTable::~OpenHashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void OpenHashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": ";
        if (this->states[i] == OPEN_EMPTY){
            out << "empty" << endl;
        }
        else if (this->states[i] == OPEN_OCCUPIED){
            HashNode* cur;
            cur = table[i];
            while(cur->next != NULL){
                out << cur->key ;
                out << ", ";
                cur = cur->next;
            }
            out << cur->key << endl;
        }
        else{
            out << "unknown state" << endl;
        }
    }
}

void OpenHashTable::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int hash_index = hf->openhashing(key);
    if (states[hash_index] == OPEN_EMPTY) { // OPEN_EMPTY
        table[hash_index] = new HashNode(key);
        states[hash_index] = OPEN_OCCUPIED;
    } else { // OPEN_OCCUPIED
        HashNode* cur;
        cur = table[hash_index];
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = new HashNode(key);
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
