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
    // if the node has a higher count than 1
    if (findNode(key)->count > 1) {
        findNode(key)->count--;
        return;
    }
    Node *parent = nullptr;
    Node *curr = root;
    Node *succ = nullptr;
    Node *pre = nullptr;

    while (curr != nullptr) {
        if (curr->str == key) {
            // remove leaf
            if (curr->left == nullptr && curr->right == nullptr) {
                if (parent == nullptr) {
                    root = nullptr;
                } else if (parent->left == curr) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
                // remove node that has a left child
            } else if (curr->left != nullptr) {
                pre = curr->left;
                if (pre->right != nullptr) {
                    while (pre->right != nullptr) {
                        pre = pre->right;
                    }
                    string cpy = pre->str;
                    remove(pre->str);
                    curr->str = cpy;
                } else {
                    Node *hold = curr->right;
                    pre->right = hold;
                    if (parent == nullptr) {
                        root = pre;
                    } else if (parent->left == curr) {
                        parent->left = pre;
                    } else {
                        parent->right = pre;
                    }
                }
                // remove node that only has a right child
            } else {
                succ = curr->right;
                if (succ->left != nullptr) {
                    while (succ->left != nullptr) {
                        succ = succ->left;
;                    }
                    string cpy = succ->str;
                    remove(succ->str);
                    curr->str = cpy;
                } else {
                    Node *hold = curr->left;
                    succ->left = hold;
                    if (parent == nullptr) {
                        root = succ;
                    } else if (parent->left == curr) {
                        parent->left = succ;
                    } else {
                        parent->right = succ;
                    }
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
    Node *find = findNode(str);
    int height = getHeight(find);
    return height;
}

Node * BSTree::findNode(string key) const {
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

int BSTree::getHeight(Node *node) const {
    if (node == nullptr) {
        return -1;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return 1 + max(leftHeight, rightHeight);
}

