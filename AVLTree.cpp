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

    // Insertion
    while (curr) {
        
        // Traverse left
        if (key < curr->key) {

            if (!curr->left) {              
                curr->left = new Node(key);
                curr->left->parent = curr;
                updateHeight(curr->left);
                rebalance(curr->left);
                return;
            }
            curr = curr->left;
        }

        // Traverse right
        else if (key > curr->key) {

            if (!curr->right) {
                curr->right = new Node(key);
                curr->right->parent = curr;
                updateHeight(curr->right);
                rebalance(curr->right);
                return;
            }
            curr = curr->right;
        }
    }
}

void AVLTree::updateHeight(Node* curr) {
    while (curr) {
        curr = curr->parent;
        curr->height++;
    }
}

Node* AVLTree::findUnbalanceFactors(Node* curr) {

    int balanceFactor;

    while (curr) {
        
        // If right subtree does not exist
        if (curr->left && !curr->right) {
            balanceFactor = curr->left->height + 1;
        }
        // If left subtree does not exist
        else if (!curr->left && curr->right) {
            balanceFactor = -1 + curr->right->height;
        }
        // If both subtrees exist
        else if (curr->left && curr->right) {
            balanceFactor = curr->left->height - curr->right->height;
        }
        // If both subtrees dont exist
        else {
            balanceFactor = 0;
        }

        // If subtree is not balanced
        if (balanceFactor != 1 || balanceFactor != 0 || balanceFactor != -1) {
            return curr;
        }
        // If subtree is balanced, traverse to parent
        else {
            curr = curr->parent;
        }
    }

    return nullptr;
}

void AVLTree::rebalance(Node* node) {

    Node* unbalancedFactor = findUnbalanceFactors(node);

    // If tree is already balanced
    if (!unbalancedFactor) {
        return;
    }
    // If tree is not balanced
    else {

        // CASE 1: left-left (2, 1)
        if (node->height == 2 && node->left->height == 1) {
            rotateRight(node);
        }

        // CASE 2: left-right (2, -1)
        else if (node->height == 2 && node->left->height == -1) {
            rotateLeft(node->left);
            rotateRight(node);
        }

        // CASE 3: right-right (-2, -1)
        else if (node->height == -2 && node->left->height == -1) {
            rotateLeft(node);
        }

        // CASE 4: right-left (-2, 1)
        else if (node->height == -2 && node->left->height == 1) {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
}

void AVLTree::rotateLeft(Node* node) {
    
}

void AVLTree::rotateRight(Node* node) {

}

void AVLTree::printBalanceFactors(Node* node) const {

    if (!node) return;

    printBalanceFactors(node->left);
    cout << node->key << "(" << balanceFactor << "), ";

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