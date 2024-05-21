#include "AVLTree.h"
#include <fstream>
using namespace std;

void AVLTree::visualizeTree(const string &outputFilename) const{
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

void AVLTree::visualizeTree(ofstream & outFS, Node *n) const{
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