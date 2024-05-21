#pragma once

#include "Node.h"

#include <iostream>
#include <string>

using std::ofstream;
using std::string;

class AVLTree {
    private:
        Node* root;
        
    public:
        // Constructor
        AVLTree();

        // Rule of three
        ~AVLTree();
        AVLTree(const AVLTree&) = delete;
        AVLTree& operator=(const AVLTree&) = delete;

        // Mutator functions
        void insert(const string&);
         
        // Accessor functions
        int balanceFactor(Node*) const;
        void printBalanceFactors() const;
        void visualizeTree(const string&) const;

    private:
        // Helper functions
        Node* findUnbalanceNode() const;
        void rotate();
        void rotateLeft();
        void rotateRight();
        void printBalanceFactors(Node*) const;
        void visualizeTree(ofstream&, Node*) const;
};