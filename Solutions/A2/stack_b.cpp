#include <iostream>
#include <stdexcept>
#include "stack_b.h"
using namespace std;

// Constructor
Stack_B::Stack_B(){
    try{
        stk = new int[1024];
    }
    catch (bad_alloc & ba){
        __throw_runtime_error("Out of Memory");
    }
    size = 0;
    capacity = 1024;
}

// Destructor
Stack_B::~Stack_B(){
    delete[] stk;
}

void Stack_B::push(int data){
    if (size == capacity){
        try{
            int* ptr_to_new = new int[capacity*2];
            for (int i = 0; i < size; i++){
                *(ptr_to_new + i) = *(stk + i);
            }
            delete[] stk;
            stk = ptr_to_new;
            *(stk + size) = data;
            size += 1;
            capacity *= 2;
        }
        catch (bad_alloc & ba){
            __throw_runtime_error("Out of memory");
        }
    }
    else{
        *(stk + size) = data;
        size += 1;
        return;
    }
}

int Stack_B::pop(){
    if (size == 0){
        __throw_runtime_error("Empty Stack");
    }
    else if (size - 1 == (capacity / 2 / 2) and size > 513){
        try{
            int temp = *(stk + size - 1);
            int* ptr_to_new = new int[capacity / 2 / 2];
            for (int i = 0; i < size-1; i++){
                *(ptr_to_new + i) =  *(stk + i);
            }
            delete[] stk;
            stk = ptr_to_new;
            size -= 1;
            capacity /= 4;
            return temp;
        }
        catch (bad_alloc & ba){
            __throw_runtime_error("Out of Memory");
        }
    }
    else{
        size -= 1;
        return *(stk + size);
    }
}

int Stack_B::get_element_from_top(int idx){
    if (idx > size - 1 || idx < 0){
        __throw_runtime_error("Index out of range");
    }
    else{
        return *(stk + (size - idx - 1));
    }
}

int Stack_B::get_element_from_bottom(int idx){
    if (idx > size - 1 || idx < 0){
        __throw_runtime_error("Index out of range");
    }
    else{
        return *(stk + idx);
    }
}

void Stack_B::print_stack(bool top_or_bottom){
    if (size == 0){
        return;
    }
    else{
        if (top_or_bottom == 1){
            for (int i = size-1; i > -1; i--){
                cout<<*(stk + i)<<"\n";
            }
            return;
        }
        else{
            for (int i = 0; i < size; i++){
                cout<<*(stk + i)<<"\n";
            }
            return;
        }
    }
}

int Stack_B::add(){
    if (size < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        int ele1 = this->pop();
        int ele2 = this->pop();
        this->push(ele1 + ele2);
        return get_element_from_top(0);
    }
}
int Stack_B::subtract(){
    if (size < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        int ele1 = this->pop();
        int ele2 = this->pop();
        this->push(ele2 - ele1);
        return get_element_from_top(0);
    }
}
int Stack_B::multiply(){
    if (size < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        int ele1 = this->pop();
        int ele2 = this->pop();
        this->push(ele1 * ele2);
        return get_element_from_top(0);
    }
}
int Stack_B::divide(){
    if (size < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        if (get_element_from_top(0) == 0){
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

int* Stack_B::get_stack(){
    return stk;
}

int Stack_B::get_size(){
    return size;
}