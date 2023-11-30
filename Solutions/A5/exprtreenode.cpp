/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    left = NULL;
    right = NULL;
    num = 0;
    id = ":=";
    type = "VAL";
}

ExprTreeNode::ExprTreeNode(string t,int v){
    left = NULL;
    right = NULL;
    num = v;
    type = t;
    id = "notagain!!";
}

ExprTreeNode::~ExprTreeNode(){
    if (left != NULL){
        delete left;
        delete right;
    }
}