#include<iostream>
#include<stdexcept>
#include "node.h"
using namespace std;

Node::Node(bool sentinel){
    is_sentinel = sentinel;
}
Node::Node(int v, Node* nxt, Node* prv){
    value = v;
    next = nxt;
    prev = prv;
    is_sentinel = false;
    this->next->prev = this;
    this->prev->next = this;
}
bool Node::is_sentinel_node(){
    return is_sentinel;
}
int Node::get_value(){
    return value;
}