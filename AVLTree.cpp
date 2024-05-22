#include "AVLTree.h"
#include <fstream>
using namespace std;

void AVLTree::insert(const string& key) {

    // If tree is empty
    if (!root) {
        root = new Node(key);
        return;
    }

    Node* curr = root;
    Node* parent = nullptr;

    // Traverse tree
    while (curr) {

        parent = curr;

        // Traverse left
        if (key < curr->key) {
            curr = curr->left;
        }
        // Traverse right
        else if (key > curr->key) {
            curr = curr->right;
        }
        // Key already exists
        else {
            return;
        }
    }

    // Insert new node
    Node* newNode = new Node(key);
    newNode->parent = parent;

    if (key < parent->key) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
}

void AVLTree::updateBalanceFactors(Node* curr) {

    // Traverse ancestors starting from new node leaf
    while (curr) {

        // Update balance factor if parent exists
        if (curr->parent) {
            
            if (curr == curr->parent->left) {
                curr->parent->balanceFactor++;
            }
            else {
                curr->parent->balanceFactor--;
            }  
        }

        curr = curr->parent;
    }
}

void AVLTree::rebalance(Node* curr) {

    // Traverse up from new node leaf and find imbalance
    while (curr) {

        if (curr->balanceFactor == 2 || curr->balanceFactor == -2) {
            
            if (curr->balanceFactor == 2) {

                // CASE 1: left-left (2, 1)
                if (curr->left->balanceFactor >= 0) {
                    rotateRight(curr);
                }

                // CASE 2: left-right (2, -1)
                else {
                    rotateLeft(curr->left);
                    rotateRight(curr);
                }
            }
            
            else if (curr->balanceFactor == -2) {

                // CASE 3: right-right (-2, -1)
                if (curr->right->balanceFactor <= 0) {
                    rotateLeft(curr);
                }

                // CASE 4: right-left (-2, 1)
                else {
                    rotateRight(curr->right);
                    rotateLeft(curr);
                }
            }
        }
        curr = curr->parent;
    }
}

void AVLTree::rotateLeft(Node* node) {

    Node* newNode = node->right;
    node->right = newNode->left;

    if (newNode->left) {
        newNode->left->parent = node;
    }

    newNode->parent = node->parent;

    if (!node->parent) {
        root = newNode;
    }
    else if (node == node->parent->left) {
        node->parent->left = newNode;
    }
    else {
        node->parent->right = newNode;
    }

    newNode->left = node;
    node->parent = newNode;
    
    // Update balance factors
    node->balanceFactor = node->balanceFactor - 1 - max(newNode->balanceFactor, 0);
    newNode->balanceFactor = newNode->balanceFactor - 1 + min(node->balanceFactor, 0);
}

void AVLTree::rotateRight(Node* node) {

    Node* newNode = node->left;
    node->left = newNode->right;

    if (newNode->right) {
        newNode->right->parent = node; 
    } 

    newNode->parent = node->parent;

    if (!node->parent) {
        root = newNode;
    } 
    else if (node == node->parent->right) {
        node->parent->right = newNode;
    }
    else {
        node->parent->left = newNode;
    } 

    newNode->right = node;
    node->parent = newNode;

    // Update balance factors
    node->balanceFactor = node->balanceFactor + 1 - min(newNode->balanceFactor, 0);
    newNode->balanceFactor = newNode->balanceFactor + 1 + max(node->balanceFactor, 0);
}

void AVLTree::printBalanceFactors(Node* node) const {

    if (!node) return;

    printBalanceFactors(node->left);
    cout << node->key << "(" << node->balanceFactor << "), ";
    printBalanceFactors(node->right);
}

void AVLTree::visualizeTree(const string &outputFilename) const {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n) const {
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->key <<" -> " <<n->left->key<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->key <<" -> " <<n->right->key<<";"<<endl;    
        }
    }
}