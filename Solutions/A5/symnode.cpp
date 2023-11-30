/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key = "what node doesn't have a key";
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    return new SymNode();
}

SymNode* SymNode::RightRightRotation(){
    return new SymNode();
}

SymNode* SymNode::LeftRightRotation(){
    return new SymNode();
}

SymNode* SymNode::RightLeftRotation(){
    return new SymNode();
}

SymNode::~SymNode(){
    if (left != NULL){
        left->par = NULL;
        delete left;
    }
    if (right != NULL){
        right->par = NULL;
        delete right;
    }
    if (par != NULL){
        if (par->right == this){
            par->right = NULL;
        }
        else{
            par->left = NULL;
        }
    }
}