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
        ~AVLTree() { destroyTree(root); }            // Destructor
        AVLTree(const AVLTree&) = delete;            // Remove default copy constructor
        AVLTree& operator=(const AVLTree&) = delete; // Remove default copy assignment operator

        // Mutator functions
        void insert(const string&); // Insert new value into tree
         
        // Accessor functions
        void printBalanceFactors() const { printBalanceFactors(root); } // Print tree with each node's balance factor
        void visualizeTree(const string&) const;                        // Create a dotty file of the tree

    private:
        // Helper functions
        void updateBalanceFactors(Node*); // Traverse through ancestors to update the balance factors of each node
        void rebalance(Node*);            // Traverse the tree and rebalance 

        void rotateLeft(Node*);  // Perform left rotation on a node 
        void rotateRight(Node*); // Perform right rotation on a node
        
        void printBalanceFactors(Node*) const;      // Recursively traverse the tree to print
        void visualizeTree(ofstream&, Node*) const; // Traverse the tree for the public visualizeTree function

        void destroyTree(Node* curr) { // Recursively destroy the tree

            if (!curr) return;

            destroyTree(curr->left);
            destroyTree(curr->right);

            delete curr;
        }
};