#pragma once
#include "bst.h"

using namespace std;

class AVLTree: public BinarySearchTree {
public:
    AVLTree() { };
    ~AVLTree() { };

    string insertion(int key);
    string deletion(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    int getHeight(Node *node);
    int getBalanceFactor(Node *node);
    
    Node *rightRotate(Node *pivot);
    Node *leftRotate(Node *pivot);

    Node* _insertion(Node *cur, int key, std::string &result);
    Node* _deletion(Node *cur, int key, std::string &result);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};