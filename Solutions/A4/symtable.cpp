/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
using namespace std;

SymbolTable::SymbolTable(){
    size = 0;
    root = new SymEntry();
}

SymbolTable::~SymbolTable(){
    delete root;
}

SymEntry* SymbolTable::get_root(){
    return this->root;
}

int SymbolTable::get_size(){
    return size;
}

void SymbolTable::remove(string k){
    SymEntry* ptr = this->root;
    SymEntry* parent = NULL;
    string s = ptr->key;
    bool c = 1;
    while (c){
        int val = s.compare(k);
        if (val == 0){
            c = 0;
            break;
        }
        else if (val > 0){
            if (ptr->left == NULL){
                return;
            }
            else{
                parent = ptr;
                ptr = ptr->left;
            }
        }
        else{
            if (ptr->right == NULL){
                return;
            }
            else{
                parent = ptr;
                ptr = ptr->right;
            }
        }
    }
    size--;
    if (ptr->right == NULL && ptr->left == NULL){
        if (parent->right == ptr){
            parent->right = NULL;
        }
        else{
            parent->left = NULL;
        }
        delete ptr->val;
        delete ptr;
    }
    else if (ptr->right == NULL){
        if (parent->right == ptr){
            parent->right = ptr->left;
        }
        else{
            parent->left = ptr->left;
        }
        delete ptr->val;
        delete ptr;
    }
    else if (ptr->left == NULL){
        if (parent->right == ptr){
            parent->right = ptr->right;
        }
        else{
            parent->left = ptr->right;
        }
        delete ptr->val;
        delete ptr;
    }
    else{
        SymEntry* parent = ptr;
        SymEntry* ptr2 = ptr->left;
        while (ptr2->right != NULL){
            parent = ptr2;
            ptr2 = ptr2->right;
        }
        swap(ptr2->key, ptr->key);
        delete ptr->val;
        ptr->val = ptr2->val;
        parent->right = ptr2->left;
        // delete ptr2;
    }
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* ptr = this->root;
    bool found = 0;
    while (!found){
        int c = ptr->key.compare(k);
        if (c == 0){
            found = 1;
        }
        else if (c == 1){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }
    return ptr->val;
}

void SymbolTable::insert(string k, UnlimitedRational* v){
    if (size == 0){
        delete root;
        this->root = new SymEntry(k, v);
        size++;
        return;
    }
    SymEntry* ptr = this->root;
    while (true){
        int c = ptr->key.compare(k);
        if (c == 0){
            delete ptr->val;
            ptr->val = v;
            return;
        }
        else if (c == 1){
            if (ptr->left == NULL){
                SymEntry* x = new SymEntry(k, v);
                ptr->left = x;
                size++;
                return;
            }
            else{
                ptr = ptr->left;
            }
        }
        else{
            if (ptr->right == NULL){
                SymEntry* x = new SymEntry(k, v);
                ptr->right = x;
                size++;
                return;
            }
            else{
                ptr = ptr->right;
            }
        }
    }
}