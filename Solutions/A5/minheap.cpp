/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// #include "heapnode.cpp"
//Write your code below this line

MinHeap::MinHeap(){
    size = 0;
    root = new HeapNode();
}

void MinHeap::push_heap(int num){
    if (size == 0){
        root->val = num;
        size++;
        return;
    }
    int x = size + 1;
    string bin = "";
    while (x >= 2){
        if (x % 2 == 0){
            bin += "0";
        }
        else{
            bin += "1";
        }
        x = x>>1;
    }
    HeapNode* ptr = root;
    for (int i = int(bin.size()) - 1; i >= 1; i--){
        if (bin[i] == '1'){
            ptr = ptr->right;
        }
        else{
            ptr = ptr->left;
        }
    }
    HeapNode* node = new HeapNode(num);
    node->par = ptr;
    if (bin[0] == '0'){
        ptr->left = node;
    }
    else{
        ptr->right = node;
    }
    size++;
    bool c = true;
    while (c){
        if (node->par == NULL){
            c = false;
            continue;
        }
        if (node->val < node->par->val){
            swap(node->val, node->par->val);
            node = node->par;
        }
        else{
            c = false;
        }
    }
    return;
}

int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    if (size == 0){
        return;
    }
    if (size == 1){
        size --;
        return;
    }
    int x = size;
    string bin = "";
    while (x >= 2){
        if (x % 2 == 0){
            bin += "0";
        }
        else{
            bin += "1";
        }
        x = x>>1;
    }
    HeapNode* ptr = root;
    for (int i = int(bin.size()) - 1; i >= 0; i--){
        if (bin[i] == '1'){
            ptr = ptr->right;
        }
        else{
            ptr = ptr->left;
        }
    }
    root->val = ptr->val;
    if (ptr->par->left == ptr){
        ptr->par->left = NULL;
    }
    else{
        ptr->par->right = NULL;
    }
    ptr->par = NULL;
    delete ptr;
    bool c = true;
    HeapNode* curr = root;
    while (c){
        if (curr->left == NULL){
            c = false;
            continue;
        }
        int swapu = -1;
        if (curr->val > curr->left->val){
            swapu = 0;
        }
        if (curr->right != NULL && curr->val > curr->right->val && curr->right->val < curr->left->val){
            swapu = 1;
        }
        if (swapu == -1){
            c = false;
            continue;
        }
        else{
            if (swapu == 0){
                swap(curr->val, curr->left->val);
                curr = curr->left;
            }
            else{
                swap(curr->val, curr->right->val);
                curr = curr->right;
            }
        }
    }
    size--;
    return;
}

MinHeap::~MinHeap(){
    delete root;
    size = 0;
}