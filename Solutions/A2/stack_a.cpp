#include <iostream>
#include <stdexcept>
#include "stack_a.h"
using namespace std;

// Constructor
Stack_A::Stack_A(){
    size = 0;
}

void Stack_A::push(int data){
    if (size == 1024){
        __throw_runtime_error("Stack Full");
    }
    else{
        stk[size] = data;
        size += 1;
        return;
    }
}

int Stack_A::pop(){
    if (size == 0){
        __throw_runtime_error("Empty Stack");
    }
    else{
        int temp = stk[size-1];
        size -= 1;
        return temp;
    }
}

int Stack_A::get_element_from_top(int idx){
    if (idx > size - 1 || idx < 0){
        __throw_runtime_error("Index out of range");
    }
    else{
        return stk[size - idx - 1];
    }
}

int Stack_A::get_element_from_bottom(int idx){
    if (idx > size - 1 || idx < 0){
        __throw_runtime_error("Index out of range");
    }
    else{
        return stk[idx];
    }
}

void Stack_A::print_stack(bool top_or_bottom){
    if (size == 0){
        return;
    }
    if (top_or_bottom == 1){
        for (int i = size-1; i > -1; i--){
            cout<<stk[i]<<"\n";
        }
        return;
    }
    else{
        for (int i = 0; i < size; i++){
            cout<<stk[i]<<"\n";
        }
        return;
    }
}

int Stack_A::add(){
    if (size < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        stk[size-2] = stk[size-1] + stk[size-2];
        size -= 1;
        return stk[size-1];
    }
}

int Stack_A::subtract(){
    if (size < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        stk[size-2] = stk[size-2] - stk[size-1];
        size -= 1;
        return stk[size-1];
    }
}

int Stack_A::multiply(){
    if (size < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else{
        stk[size-2] = stk[size-1] * stk[size-2];
        size -= 1;
        return stk[size-1];
    }
}

int Stack_A::divide(){
    if (size < 2){
        __throw_runtime_error("Not Enough Arguements");
    }
    else if (stk[size-1] == 0){
        size -= 2;
        __throw_runtime_error("Division by Zero Error");
    }
    else{
        if (stk[size-2] * stk[size-1] >= 0){
            stk[size-2] = stk[size-2] / stk[size-1];
        }
        else{
            if (stk[size-2] % stk[size-1] == 0){
                stk[size-2] = stk[size-2] / stk[size-1];
            }
            else{
                stk[size-2] = (stk[size-2] / stk[size-1]) - 1;
            }
        }
        size -= 1;
        return stk[size-1];
    }
}

int* Stack_A::get_stack(){
    int* ptr = stk;
    return ptr;
}

int Stack_A::get_size(){
    return size;
}
