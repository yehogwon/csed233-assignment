#include <iostream>
#include <fstream>
#include <string>
#include "closed_hash_function.h"
#include "closed_hash_table.h"

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

ClosedHashTable::ClosedHashTable(int table_size, ClosedHashFunction *hf) : table_size(table_size) {
    this->hf = hf;
    this->table = new int[this->table_size];
    this->states = new ClosedTableState[this->table_size];

    for (int i = 0; i < this->table_size; ++i) {
            this->states[i] = CLOSED_EMPTY;
    }
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

ClosedHashTable::~ClosedHashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void ClosedHashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": ";
        if (this->states[i] == CLOSED_EMPTY)
            out << "empty" << endl;
        else if (this->states[i] == CLOSED_OCCUPIED)
            out << this->table[i] << endl;
        else
            out << "unknown state" << endl;
    }
    out << "F: ";
    this->flist.print(out);
}

void ClosedHashTable::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int attempts = 0;
    while (attempts < table_size && states[hf->closedhashing(key, attempts)] == CLOSED_OCCUPIED)
        attempts++;
    if (attempts == table_size) {
        flist.add(key);
    } else {
        table[hf->closedhashing(key, attempts)] = key;
        states[hf->closedhashing(key, attempts)] = CLOSED_OCCUPIED;
    }
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
