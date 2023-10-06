/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    this->type = "EQ";
    this->id = ":=";
    left = NULL;
    right = NULL;
    val = nullptr;
    evaluated_value = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    this->type = "VAL";
    this->id = "blahblah";
    left = NULL;
    right = NULL;
    UnlimitedInt* one = new UnlimitedInt(1);
    evaluated_value = new UnlimitedRational(v, one);
    delete one;
    val = evaluated_value;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    this->type = t;
    this->id = "crying";
    left = NULL;
    right = NULL;
    evaluated_value = v;
    val = evaluated_value;
}

ExprTreeNode::~ExprTreeNode(){
    if (this->type.compare("VAR") != 0 && this->type.compare("EQ") != 0){
        delete evaluated_value;
    }
    if (this->left != NULL){
        delete left;
        delete right;
    }
}