#pragma once

#include <string>

using std::string;

class Node {

    friend class AVLTree;

    public: 
        Node(const string& key): key(key), balanceFactor(0), parent(nullptr), left(nullptr), right(nullptr) {}

    private: 
        // Data
        string key;
        int balanceFactor;

        // Pointers
        Node* parent;
        Node* left;
        Node* right;
};