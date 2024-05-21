#pragma once

#include <string>

using std::string;

class Node {

    friend class AVLtree;

    public: 
        Node(const string& key): key(key), left(nullptr), right(nullptr) {}

    private: 
        string key;
        Node* left;
        Node* right;
};