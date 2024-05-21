#include "AVLTree.h"
#include <fstream>
using namespace std;

void AVLTree::insert(const string& key) {

    // If tree is empty
    if (!root) {
cout << "root is empty, creating new root" << endl;
        root = new Node(key);
        return;
    }

    Node* curr = root;

    while (curr) {

        // Traverse left
        if (key < curr->key) {
cout << "key is less than curent node, " << curr->key << endl;
            if (!curr->left) {
cout << curr->key << " is a leaf node, inserting" << endl;                
                curr->left = new Node(key);
                return;
            }
cout << "travsering left" << endl;
            curr = curr->left;
        }

        // Traverse right
        else if (key > curr->key) {
cout << "key is greater than curent node, " << curr->key << endl;
            if (!curr->right) {
cout << curr->key << " is a leaf node, inserting" << endl;                
                curr->right = new Node(key);
                return;
            }
cout << "travsering right" << endl;
            curr = curr->right;
        }

        // Key already exists
        else {
            throw runtime_error("Key already exists.");
        }
    }
}

void AVLTree::printBalanceFactors(Node* node) const {

    if (!node) return;
    
    cout << node->key << ", ";

    printBalanceFactors(node->left);
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