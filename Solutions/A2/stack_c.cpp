#include<iostream>
#include<stdexcept>
#include "list.h"
#include "stack_c.h"
using namespace std;

Stack_C::Stack_C(){
    try{
        stk = new List();
    }
    catch (bad_alloc & ba){
        __throw_runtime_error("Out of Memory");
    }
}

Stack_C::~Stack_C(){
    delete stk;
}

void Stack_C::push(int data){
    try{
        stk->insert(data);
    }
    catch (bad_alloc & ba){
        __throw_runtime_error("Out of Memory");
    }
}

int Stack_C::pop(){
    if (stk->get_size() == 0){
        __throw_runtime_error("Empty Stack");
    }
    else{
        return stk->delete_tail();
    }
}

int Stack_C::get_element_from_top(int idx){
    if (stk->get_size() -  1< idx || idx < 0){
        __throw_runtime_error("Index out of range");
    }
    else{
        Node* ptr = stk->get_head()->next;
        int s = stk->get_size();
        int cnt = 1;
        while (cnt < s - idx){
            ptr = ptr->next;
            cnt += 1;
        }
        return ptr->get_value();
    }
}

int Stack_C::get_element_from_bottom(int idx){
    if (idx > stk->get_size() - 1 || idx < 0){
        __throw_runtime_error("Index out of range");
    }
    else{
        int cnt = 0;
        Node* ptr = stk->get_head()->next;
        while (cnt < idx){
            ptr = ptr->next;
            cnt += 1;
        }
        return ptr->get_value();
    }
}

void Stack_C::print_stack(bool top_or_bottom){
    if (stk->get_size() == 0){
        return;
    }
    else{
        Node* ptr = stk->get_head();
        if (top_or_bottom == 1){
            while(ptr->next->next != NULL){
                ptr = ptr->next;
            }
            while(ptr->prev->prev != NULL){
                cout<<ptr->get_value()<<"\n";
                ptr = ptr->prev;
            }
            return;
        }
        else{
            while(ptr->next->next != NULL){
                ptr = ptr->next;
                cout<<ptr->get_value()<<"\n";
            }
            return;
        }
    }
}

int Stack_C::add(){
    if (stk->get_size() < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        int res = this->pop() + this->pop();
        this->push(res);
        return res;
    }
}

int Stack_C::subtract(){
    if (stk->get_size() < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        int ele1 = this->pop();
        int ele2 = this->pop();
        int res = ele2 - ele1;
        this->push(res);
        return res;
    }
}

int Stack_C::multiply(){
    if (stk->get_size() < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        int res = this->pop() * this->pop();
        this->push(res);
        return res;
    }
}

int Stack_C::divide(){
    if (stk->get_size() < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        if (this->get_element_from_top(0) == 0){
            __throw_runtime_error("Divide by Zero");
        }
        else{
            int ele1 = this->pop();
            int ele2 = this->pop();
            int res;
            if (ele1 * ele2 >= 0){
                res = (ele2 / ele1);
            }
            else{
                if (ele2 % ele1 == 0){
                    res = (ele2 / ele1);
                }
                else{
                    res = ((ele2 / ele1) - 1);
                }
            }
            this->push(res);
            return res;
        }
    }
}

List* Stack_C::get_stack(){
    return stk;
}

int Stack_C::get_size(){
    return stk->get_size();
}