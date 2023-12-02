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
    return node->height;
}

int AVLTree::getBalanceFactor(Node *node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rightRotate(Node *pivot) {
    Node *pivotLeft = pivot->left;
    pivot->left = pivotLeft->right;
    pivotLeft->right = pivot;

    pivot->height = std::max(getHeight(pivot->left), getHeight(pivot->right)) + 1;
    pivotLeft->height = std::max(getHeight(pivotLeft->left), getHeight(pivotLeft->right)) + 1;

    return pivotLeft;
}

Node* AVLTree::leftRotate(Node *pivot) {
    Node *pivotRight = pivot->right;
    pivot->right = pivotRight->left;
    pivotRight->left = pivot;

    pivot->height = std::max(getHeight(pivot->left), getHeight(pivot->right)) + 1;
    pivotRight->height = std::max(getHeight(pivotRight->left), getHeight(pivotRight->right)) + 1;

    return pivotRight;
}

Node* AVLTree::_insertion(Node *cur, int key, std::string &result) {
    Node *n = new Node(key);
    n->height = 1;

    if (cur == NULL) {
        result = "OK";
        return n;
    }
    
    if (key < cur->key) cur->left = _insertion(cur->left, key, result);
    else if (key > cur->key) cur->right = _insertion(cur->right, key, result);
    else {
        result = "Fail";
        throw "Duplicate key";
    }

    cur->height = std::max(getHeight(cur->left), getHeight(cur->right)) + 1;
    int bf = getBalanceFactor(cur);

    if (bf < -1) {
        if (key > cur->right->key) {
            result = "RR";
            return leftRotate(cur);
        } else {
            result = "RL";
            cur->right = rightRotate(cur->right);
            return leftRotate(cur);
        }
    } else if (bf > 1) {
        if (key < cur->left->key) {
            result = "LL";
            return rightRotate(cur);
        } else {
            result = "LR";
            cur->left = leftRotate(cur->left);
            return rightRotate(cur);
        }
    }

    if (result == "DS") result = "OK";
    return cur;
}

Node* AVLTree::_deletion(Node *cur, int key, std::string &result) {
    if (cur == NULL) {
        result = "Fail";
        return cur;
    }

    if (key < cur->key) cur->left = _deletion(cur->left, key, result);
    else if (key > cur->key) cur->right = _deletion(cur->right, key, result);
    else {
        result = "OK";
        if (cur->left == NULL || cur->right == NULL) {
            Node *temp = cur->left ? cur->left : cur->right;
            if (temp == NULL) {
                temp = cur;
                cur = NULL;
            } else {
                *cur = *temp;
            }
            delete temp;
        } else {
            Node *temp = cur->right;
            while (temp->left != NULL) temp = temp->left;
            cur->key = temp->key;
            cur->right = _deletion(cur->right, temp->key, result);
        }
    }

    if (cur == NULL) return cur;

    cur->height = std::max(getHeight(cur->left), getHeight(cur->right)) + 1;
    int bf = getBalanceFactor(cur);

    if (bf < -1) {
        if (getBalanceFactor(cur->right) <= 0) {
            return leftRotate(cur);
        } else {
            cur->right = rightRotate(cur->right);
            return leftRotate(cur);
        }
    } else if (bf > 1) {
        if (getBalanceFactor(cur->left) >= 0) {
            return rightRotate(cur);
        } else {
            cur->left = leftRotate(cur->left);
            return rightRotate(cur);
        }
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
    try {
        _root = _insertion(_root, key, result);
    } catch (const char *msg) {
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
    _root = _deletion(_root, key, result);
    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}