#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int BinarySearchTree::insertion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (_root == NULL) {
        _root = new Node(key);
        return 0;
    }

    Node *cur = _root;
    while (cur != NULL) {
        if (key < cur->key) {
            if (cur->left == NULL) {
                cur->left = new Node(key);
                return 0;
            }
            cur = cur->left;
        } else if (key > cur->key) {
            if (cur->right == NULL) {
                cur->right = new Node(key);
                return 0;
            }
            cur = cur->right;
        } else {
            return -1;
        }
    }
    
    return -1;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::deletion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    if (_root == NULL) {
        return -1;
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
        return -1;
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

    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int BinarySearchTree::findNthMinimum(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    std::string inorder = this->inOrder();
    std::istringstream iss(inorder);
    std::string token;

    while (std::getline(iss, token, ' ')) {
        if (key == 1) {
            return std::stoi(token);
        }
        key--;
    }

    return -1;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}