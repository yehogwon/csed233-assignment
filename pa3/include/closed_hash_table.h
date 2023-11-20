#pragma once
#include <iostream>
#include <string>
#include "closed_hash_function.h"
using namespace std;

class FailedNode {
  public:
    int key;
    FailedNode *next;
    FailedNode(int key){
        this->key = key;
        this->next = NULL;
    }
};

class FailedList {
private:
    FailedNode *head;

public:
    FailedList() : head(nullptr) {}

    void add(int key) {
        FailedNode *newNode = new FailedNode(key);
        if (head == nullptr) {
            head = newNode;
        } else {
            FailedNode *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    void print(ostream &out) {
        if (head == nullptr) {
            out << "empty" << endl;
        } else {
            FailedNode *current = head;
            while (current != nullptr) {
                out << current->key;
                if (current->next != nullptr) {
                    out << ", ";
                }
                current = current->next;
            }
            out << endl;
        }
    }

    ~FailedList() {
        FailedNode *current = head;
        while (current != nullptr) {
            FailedNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

enum ClosedTableState {
    CLOSED_EMPTY,
    CLOSED_OCCUPIED,
};

class ClosedHashTable {
public:
    ClosedHashTable(int table_size, ClosedHashFunction *hf);
    ~ClosedHashTable();

    void print_table(ostream &out);

    void insert(int key);

private:
    const int table_size;
    ClosedHashFunction *hf;
    int *table;
    ClosedTableState *states;
    FailedList flist;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

