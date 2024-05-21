#pragma once

#include <string>

using std::string;

class Node {

    friend class AVLTree;

    public: 
        Node(const string& key): key(key), height(0), parent(nullptr), left(nullptr), right(nullptr) {}

    private: 
        string key;
        int height;
        Node* parent;
        Node* left;
        Node* right;
};