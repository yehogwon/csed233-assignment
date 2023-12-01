#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

int AVLTree::getHeight(Node *node) {
    if (node == NULL) return 0;
    
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

int AVLTree::getBalanceFactor(Node *node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rr(Node *pivot) {
    Node *pivotRight = pivot->right;
    pivot->right = pivotRight->left;
    pivotRight->left = pivot;
    return pivotRight;
}

Node* AVLTree::ll(Node *pivot) {
    Node *pivotLeft = pivot->left;
    pivot->left = pivotLeft->right;
    pivotLeft->right = pivot;
    return pivotLeft;
}

Node* AVLTree::rl(Node *pivot) {
    pivot->right = ll(pivot->right);
    return rr(pivot);
}

Node* AVLTree::lr(Node *pivot) {
    pivot->left = rr(pivot->left);
    return ll(pivot);
}

Node* AVLTree::rebalance(Node *pivot, std::string &result) {
    int bf = getBalanceFactor(pivot);
    if (bf < -1) {
        if (getBalanceFactor(pivot->right) > 0) {
            pivot = rl(pivot);
            result = "RL";
        } else {
            pivot = rr(pivot);
            result = "RR";
        }
    } else if (bf > 1) {
        if (getBalanceFactor(pivot->left) < 0) {
            pivot = lr(pivot);
            result = "LR";
        } else {
            pivot = ll(pivot);
            result = "LL";
        }
    }
    return pivot;
}

///////////      End of Implementation      /////////////
///////////////////////////////////////////////////////

string AVLTree::insertion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    string result = "DS";
    if (!BinarySearchTree::insertion(key)) {
        Node *cur = _root;
        while (cur != NULL) {
            int bf = getBalanceFactor(cur);
            if (bf < -1 || bf > 1) break;

            if (key < cur->key) {
                cur = cur->left;
            } else if (key > cur->key) {
                cur = cur->right;
            } else {
                break;
            }
        }

        if (cur->key == key) result = "OK";
        else _root = rebalance(cur, result);
    } else {
        result = "Fail";
    }

    return result;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string AVLTree::deletion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    string result = "DS";
    if (!BinarySearchTree::deletion(key)) {
        // TODO: rebalance for deletion
        result = "OK";
    } else {
        result = "Fail";
    }
    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}