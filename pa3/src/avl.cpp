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

Node* AVLTree::_deletion(int key) {
    if (_root == NULL) {
        return NULL;
    }

    Node *cur = _root;
    Node *parent = NULL;
    while (cur != NULL) {
        if (key < cur->key) {
            parent = cur;
            cur = cur->left;
        } else if (key > cur->key) {
            parent = cur;
            cur = cur->right;
        } else {
            break;
        }
    }

    if (cur == NULL) {
        return NULL;
    }

    if (cur->left != NULL && cur->right != NULL) { // deg 2
        Node *succ = cur->right;
        Node *succ_parent = cur;
        while (succ->left != NULL) {
            succ_parent = succ;
            succ = succ->left;
        }
        cur->key = succ->key;
        if (succ_parent->left == succ) succ_parent->left = succ->right;
        else succ_parent->right = succ->right;
    } else if (cur->left != NULL) { // deg 1
        if (parent == NULL) _root = cur->left;
        else if (parent->left == cur) parent->left = cur->left;
        else parent->right = cur->left;
    } else if (cur->right != NULL) { // deg 1
        if (parent == NULL) _root = cur->right;
        else if (parent->left == cur) parent->left = cur->right;
        else parent->right = cur->right;
    } else { // deg 0
        if (parent == NULL) _root = NULL;
        else if (parent->left == cur) parent->left = NULL;
        else parent->right = NULL;
    }
    
    return cur;
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

    Node *parent = _deletion(key);
    if (parent == NULL) { 
        result = "Fail";
    } else {
        Node *deepest_parent = NULL;
        Node *deepest = _root;
        while (deepest != NULL) {
            int bf = getBalanceFactor(deepest);
            if (bf < -1 || bf > 1) break;

            if (key < deepest->key) {
                deepest_parent = deepest;
                deepest = deepest->left;
            } else if (key > deepest->key) {
                deepest_parent = deepest;
                deepest = deepest->right;
            } else {
                break;
            }
        }

        if (deepest != NULL) {
            if (deepest_parent == NULL) _root = rebalance(deepest, result);
            else if (deepest_parent->left == deepest) deepest_parent->left = rebalance(deepest, result);
            else deepest_parent->right = rebalance(deepest, result);
        }
        
        result = "OK";
    }
    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}