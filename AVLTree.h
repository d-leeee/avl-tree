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
        AVLTree() : root(nullptr) {}

        // Rule of three
        //~AVLTree();
        //AVLTree(const AVLTree&) = delete;
        //AVLTree& operator=(const AVLTree&) = delete;

        // Mutator functions
        void insert(const string&);
         
        // Accessor functions
        int balanceFactor(Node*) const;
        void printBalanceFactors() const { printBalanceFactors(root); }
        void visualizeTree(const string&) const;

    private:
        // Helper functions
        void updateHeight(Node*);
        Node* findUnbalanceFactors(Node*);
        void rebalance(Node*);

        void rotateLeft(Node*);
        void rotateRight(Node*);
        
        void printBalanceFactors(Node*) const;
        void visualizeTree(ofstream&, Node*) const;
};