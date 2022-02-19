//
// Created by Angelina Guzman on 2/9/22.
//

#include "BSTree.h"
using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

void BSTree::insert(const string &newString) {
    if(search(newString)) {
        Node *find = findNode(newString);
        find->count++;
        return;
    }

    Node *node = new Node(newString);
    if (root == nullptr) {
        root = node;
        return;
    }

    Node *curr = root;
    while (curr != nullptr) {
        if (node->str < curr->str) {
            if (curr->left == nullptr) {
                curr->left = node;
                curr = nullptr;
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->right == nullptr) {
                curr->right = node;
                curr = nullptr;
            } else {
                curr = curr->right;
            }
        }
    }
}



bool BSTree::search(const string &key) const {
    Node *curr = root;
    while (curr != nullptr) {
        if (key == curr->str) {
            return true;
        } else if (key < curr->str){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return false;
}

void BSTree::remove(const string &key) {
    if (!search(key)) {
        return;
    }
    if (findNode(key)->count > 1) {
        findNode(key)->count--;
        return;
    }
    Node *parent = nullptr;
    Node *curr = root;
    Node *succ = nullptr;

    while (curr != nullptr) {
        if (curr->str == key) {
            if (curr->left == nullptr && curr->right == nullptr) {
                if (parent == nullptr) {
                    root = nullptr;
                } else if (parent->left == curr) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            } else if (curr->right == nullptr) {
                if (parent == nullptr) {
                    root = curr->left;
                } else if (parent->left == curr) {
                    parent->left = curr->left;
                } else {
                    parent->right = curr->left;
                }
            } else if (curr->left == nullptr) {
                if (parent == nullptr) {
                    root = curr->right;
                } else if (parent->left == curr) {
                    parent->left = curr->right;
                } else {
                    parent->right = curr->right;
                }
            } else {
                succ = curr->right;
                while (succ->left != nullptr) {
                    succ = succ->left;
                    string cpy = succ->str;
                    remove(succ->str);
                    curr->str = cpy;
                }
            }
            return;
    } else if (curr->str < key) {
        parent = curr;
        curr = curr->right;
    } else {
            parent = curr;
            curr = curr->left;
        }
    }
    return;
}

string BSTree::largest() const {
    Node *curr = root;
    if (root != nullptr) {
        if (root->right != nullptr) { // if there is a right subtree
            while (curr->right != nullptr) {
                curr = curr->right;
            }
            return curr->str;
        } else {
            return root->str; // if there is no right sub tree the largest string should be the root
        }
    }
    return "";
}

string BSTree::smallest() const {
    Node *curr = root;
    if (root != nullptr) {
        if (root->left != nullptr) {
            while (curr->left != nullptr) {
                curr = curr->left;
            }
            return curr->str;
        } else {
            return root->str;
        }
    }
    return "";
}

int BSTree::height(const string &str) const {
    int count = 0;
    Node *curr = root;
    while (curr != nullptr) {
        if (str == curr->str) {
            return count;
        } else if (str < curr->str){
            curr = curr->left;
            count++;
        } else {
            curr = curr->right;
            count++;
        }
    }
    return -1;
}

Node *BSTree::findNode(string key) {
    Node *curr = root;
    while (curr != nullptr) {
        if (key == curr->str) {
            return curr;
        } else if (key < curr->str){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return nullptr;
}

void BSTree::preOrder() {
    preOrder(root);
}

void BSTree::postOrder() {
    postOrder(root);
}

void BSTree::inOrder()  {
    inOrder(root);
}

void BSTree::preOrder(Node* node) {
    if (node == nullptr) {
        return;
    }

    cout << node->str << "(" << node->count << "), ";
    preOrder(node->left);
    preOrder(node->right);
}

void BSTree::postOrder(Node* node) {
    if (node == nullptr) {
        return;
    }

    postOrder(node->left);
    postOrder(node->right);
    cout << node->str << "(" << node->count << "), ";
}

void BSTree::inOrder(Node *node) {
    if (node == nullptr) {
        return;
    }

    inOrder(node->left);
    cout << node->str << "(" << node->count << "), ";
    inOrder(node->right);
}

