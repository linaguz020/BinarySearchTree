//
// Created by Angelina Guzman on 2/9/22.
//

#ifndef PA2_NODE_H
#define PA2_NODE_H
#include <iostream>
using namespace std;



struct Node {
    string str;
    int count;

    Node *left;
    Node *right;

    Node(string);
};


#endif //PA2_NODE_H
