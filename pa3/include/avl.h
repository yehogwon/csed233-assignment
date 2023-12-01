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

    Node* rr(Node *pivot);
    Node* ll(Node *pivot);
    Node* rl(Node *pivot);
    Node* lr(Node *pivot);

    Node* rebalance(Node *pivot, std::string &result);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};