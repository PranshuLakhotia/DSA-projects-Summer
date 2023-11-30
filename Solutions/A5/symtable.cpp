/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    size = 0;
    root = new SymNode();
}


void ll_rotate(SymNode* node){
    node->left->par = node->par;
    if (node->par != NULL){
        if (node->par->left == node){
            node->par->left = node->left;
        }
        else{
            node->par->right = node->left;
        }
    }
    node->par = node->left;
    node->left = node->left->right;
    if (node->left != NULL){
        node->left->par = node;
    }
    node->par->right = node;
}

void rr_rotate(SymNode* node){
    node->right->par = node->par;
    if (node->par != NULL){
        if (node->par->right == node){
            node->par->right = node->right;
        }
        else{
            node->par->left = node->right;
        }
    }
    node->par = node->right;
    node->right = node->right->left;
    if (node->right != NULL){
        node->right->par = node;
    }
    node->par->left = node;
}

void lr_rotate(SymNode* node){
    node->left->right->par = node->par;
    if (node->par == NULL){}
    else if (node->par->left == node){
        node->par->left = node->left->right;
    }
    else{
        node->par->right = node->left->right;
    }
    node->par = node->left->right;
    node->left->par = node->left->right;
    node->left->right = node->left->right->left;
    if (node->left->right){
        node->left->right->par = node->left;
    }
    node->par->left = node->left;
    node->left = node->par->right;
    if (node->left){
        node->left->par = node;
    }
    node->par->right = node;
}

void rl_rotate(SymNode* node){
    node->right->left->par = node->par;
    if (!node->par){}
    else if (node->par->right == node){
        node->par->right = node->right->left;
    }
    else{
        node->par->left = node->right->left;
    }
    node->par = node->right->left;
    node->right->par = node->right->left;
    node->right->left = node->right->left->right;
    if (node->right->left){
        node->right->left->par = node->right;
    }
    node->par->right = node->right;
    node->right = node->par->left;
    if (node->right){
        node->right->par = node;
    }
    node->par->left = node;
}

void SymbolTable::insert(string k){
    if (size == 0){
        root->key = k;
        size ++;
        // assign address
        return;
    }
    SymNode* path[root->height + 1];
    int cnt = 0;
    SymNode* ptr = root;
    SymNode* a;
    while (true){
        int c = ptr->key.compare(k);
        if (c == 0){
            //reassign value at the memory index of variable
            return;
        }
        else if (c <= -1){
            path[cnt] = ptr;
            cnt ++;
            if (ptr->right == NULL){
                a = new SymNode(k);
                ptr->right = a;
                a->par = ptr;
                size++;
                // assign address to this variable
                break;
            }
            ptr = ptr->right;
        }
        else{
            path[cnt] = ptr;
            cnt ++;
            if (ptr->left == NULL){
                a = new SymNode(k);
                ptr->left = a;
                a->par = ptr;
                size++;
                // assign address to this variable
                break;
            }
            ptr = ptr->left;
        }
    }
    cnt --;
    while (cnt >= 0){
        SymNode* node = path[cnt];
        int lh, rh;
        if (node->left == NULL){
            lh = -1;
        }
        else{
            lh = node->left->height;
        }
        if (node->right == NULL){
            rh = -1;
        }
        else{
            rh = node->right->height;
        }
        node->height = max(lh, rh) + 1;
        if (abs(lh - rh) <= 1){
            cnt--;
            continue;
        }
        else{
            string ch = node->left == path[cnt + 1] ? "left" : "right";
            if (ch.compare("left") == 0){
                if (path[cnt + 1]->left == a || path[cnt + 1]->left == path[cnt + 2]){
                    ll_rotate(node);
                }
                else{
                    lr_rotate(node);
                }
            }
            else{
                if (path[cnt + 1]->left == a || path[cnt + 1]->left == path[cnt + 2]){
                    rl_rotate(node);
                }
                else{
                    rr_rotate(node);
                }
            }
            break;
        }
    }
    while (root->par){
        root = root->par;
    }
    if (cnt < 0){
        return;
    }
    SymNode* node = path[cnt];
    while (node){
        int lh, rh;
        if (node->left == NULL){
            lh = -1;
        }
        else{
            lh = node->left->height;
        }
        if (node->right == NULL){
            rh = -1;
        }
        else{
            rh = node->right->height;
        }
        node->height = max(lh, rh) + 1;
        node = node->par;
    }
}

void SymbolTable::remove(string k){
    SymNode* prev = NULL;
    SymNode* ptr = root;
    while (true){
        int c = ptr->key.compare(k);
        if (c == 0){
            if (ptr->left == NULL && ptr->right == NULL){
                if (ptr->par == NULL){
                    root->key = "what node doesn't have a key";
                    size --;
                    return;
                }
                else{
                    if (ptr->par->left == ptr){
                        ptr->par->left = NULL;
                    }
                    else{
                        ptr->par->right = NULL;
                    }
                    ptr->par = NULL;
                    delete ptr;
                }
            }
            else if (ptr->left == NULL){
                if (ptr->par == NULL){
                    root = ptr->right;
                    ptr->right->par = NULL;
                    ptr->right = NULL;
                    delete ptr;
                    size --;
                    return;
                }
                else if (ptr->par->left == ptr){
                    ptr->par->left = ptr->right;
                }
                else{
                    ptr->par->right = ptr->right;
                }
                ptr->right->par = ptr->par;
                ptr->right = NULL;
                ptr->par = NULL;
                delete ptr;
            }
            else if (ptr->right == NULL){
                if (ptr->par == NULL){
                    root = ptr->left;
                    ptr->left->par = NULL;
                    ptr->left = NULL;
                    delete ptr;
                    size --;
                    return;
                }
                if (ptr->par->left == ptr){
                    ptr->par->left = ptr->left;
                }
                else{
                    ptr->par->right = ptr->left;
                }
                ptr->left->par = ptr->par;
                ptr->left = NULL;
                ptr->par = NULL;
                delete ptr;
            }
            else{
                prev = ptr;
                SymNode* ptr2 = ptr->left;
                while (ptr2->right != NULL){
                    prev = ptr2;
                    ptr2 = ptr2->right;
                }
                std::swap(ptr->key, ptr2->key);
                std::swap(ptr->address, ptr2->address);
                if (prev->left = ptr2){
                    prev->left = ptr2->left;
                    if (ptr2->left){
                        ptr2->left->par = prev;
                    }
                }
                else if (ptr2->left == NULL){
                    ptr2->par->right = NULL;
                }
                else{
                    ptr2->par->right = ptr2->left;
                    ptr2->left->par = ptr2->par;
                }
                ptr2->left = NULL;
                ptr2->par = NULL;
                delete ptr2;
            }
            size --;
            //deallocate the memory index of variable
            break;
        }
        else if (c <= -1){
            if (ptr->right == NULL){
                return;
            }
            prev = ptr;
            ptr = ptr->right;
        }
        else{
            if (ptr->left == NULL){
                return;
            }
            prev = ptr;
            ptr = ptr->left;
        }
    }
    while (prev != NULL){
        int lh, rh;
        if (prev->left == NULL){
            lh = -1;
        }
        else{
            lh = prev->left->height;
        }
        if (prev->right == NULL){
            rh = -1;
        }
        else{
            rh = prev->right->height;
        }
        prev->height = max(lh, rh) + 1;
        if (abs(lh - rh) <= 1){
            prev = prev->par;
            continue;
        }
        else{
            if (lh > rh){
                int llh, lrh;
                if (prev->left->left == NULL){
                    llh = -1;
                }
                else{
                    llh = prev->left->left->height;
                }
                if (prev->left->right == NULL){
                    lrh = -1;
                }
                else{
                    lrh = prev->left->right->height;
                }
                if (llh >= lrh){
                    ll_rotate(prev);
                }
                else{
                    lr_rotate(prev);
                }
            }
            else{
                int rlh, rrh;
                if (prev->right->left == NULL){
                    rlh = -1;
                }
                else{
                    rlh = prev->right->left->height;
                }
                if (prev->right->right == NULL){
                    rh = -1;
                }
                else{
                    rrh = prev->right->right->height;
                }
                if (rlh >= rrh){
                    rl_rotate(prev);
                }
                else{
                    rr_rotate(prev);
                }
            }
        }
    }
    while (root->par != NULL){
        root = root->par;
    }
}

int SymbolTable::search(string k){
    SymNode* ptr = root;
    while (true){
        int c = ptr->key.compare(k);
        if (c == 0){
            return ptr->address;
        }
        else if (c <= -1){
            if (ptr->right == NULL){
                return -2;
            }
            ptr = ptr->right;
        }
        else{
            if (ptr->left == NULL){
                return -2;
            }
            ptr = ptr->left;
        }
    }
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* ptr = root;
    while (true){
        int c = ptr->key.compare(k);
        if (c == 0){
            ptr->address = idx;
            return;
        }
        else if (c <= -1){
            if (ptr->right == NULL){
                return;
            }
            ptr = ptr->right;
        }
        else{
            if (ptr->left == NULL){
                return;
            }
            ptr = ptr->left;
        }
    }
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    delete root;
}