/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
    left = NULL;
    right =NULL;
    this->val = nullptr;
    this->key = "hehe";
}

SymEntry::SymEntry(string k, UnlimitedRational* v){
    left = NULL;
    right = NULL;
    this->key = k;
    this->val = v;
}

SymEntry::~SymEntry(){
    if (this->left != NULL){
        delete this->left;
    }
    if (this->right != NULL){
        delete this->right;
    }
}