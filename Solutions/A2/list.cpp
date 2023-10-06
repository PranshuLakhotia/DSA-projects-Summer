#include<iostream>
#include<stdexcept>
#include "node.h"
#include "list.h"
using namespace std;

List::List(){
    size = 0;
    try{
        sentinel_head = new Node(true);
        sentinel_tail = new Node(true);
    }
    catch (bad_alloc & ba){
        __throw_runtime_error("Out of Memory");
    }
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
    sentinel_head->prev = NULL;
    sentinel_tail->next = NULL;
}

List::~List(){
    Node* ptr = sentinel_head;
    while (ptr->next != sentinel_tail){
        ptr = ptr->next;
        delete ptr->prev;
    }
    delete ptr;
    delete sentinel_tail;
}

void List::insert(int v){
    Node* ptr = new Node(v, sentinel_tail, sentinel_tail->prev);
    sentinel_tail->prev->next = ptr;
    sentinel_tail->prev = ptr;
    size += 1;
    return;
}

int List::delete_tail(){
    if (sentinel_tail->prev != sentinel_head){
        int res = sentinel_tail->prev->get_value();
        sentinel_tail->prev = sentinel_tail->prev->prev;
        delete sentinel_tail->prev->next;
        sentinel_tail->prev->next = sentinel_tail;
        size -= 1;
        return res;
    }
    else{
        __throw_runtime_error("Empty List");
    }
}

int List::get_size(){
    return size;
}

Node* List::get_head(){
    return sentinel_head;
}
