/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <iostream>
using namespace std;

Evaluator::Evaluator(){
    symtable = new SymbolTable();
}

Evaluator::~Evaluator(){
    delete symtable;
    for (int i = 0; i < int(expr_trees.size()); i++){
        delete expr_trees[i];
    }
}

void Evaluator::parse(vector<string> code){
    vector<ExprTreeNode*> stack;
    ExprTreeNode* root = new ExprTreeNode();
    root->left = new ExprTreeNode();
    root->left->id = code[0];
    root->left->type = "VAR";
    int j = 2;
    ExprTreeNode* brack_open = new ExprTreeNode();
    brack_open->type = "BR";
    brack_open->id = "(";
    while (j < int(code.size())){
        if (code[j].compare("(") == 0){
            stack.push_back(brack_open);
            j++;
            continue;
        }
        else if (code[j].compare("+") == 0){
            ExprTreeNode* op = new ExprTreeNode();
            op->type = "ADD";
            op->id = "+";
            stack.push_back(op);
            j++;
            continue;
        }
        else if (code[j].compare("-") == 0){
            ExprTreeNode* op = new ExprTreeNode();
            op->type = "SUB";
            op->id = "-";
            stack.push_back(op);
            j++;
            continue;
        }
        else if (code[j].compare("*") == 0){
            ExprTreeNode* op = new ExprTreeNode();
            op->type = "MUL";
            op->id = "*";
            stack.push_back(op);
            j++;
            continue;
        }
        else if (code[j].compare("/") == 0){
            ExprTreeNode* op = new ExprTreeNode();
            op->type = "DIV";
            op->id = "/";
            stack.push_back(op);
            j++;
            continue;
        }
        else if (code[j].compare(":=") == 0){
            ExprTreeNode* eq = new ExprTreeNode();
            stack.push_back(eq);
            j++;
            continue;
        }
        else if (code[j].compare(")") == 0){
            ExprTreeNode* r = stack.back();
            stack.pop_back();
            if (stack.back() == brack_open){
                stack.pop_back();
                stack.push_back(r);
                j++;
                continue;
            }
            else{
                ExprTreeNode* op = stack.back();
                stack.pop_back();
                ExprTreeNode* l = stack.back();
                stack.pop_back();
                stack.pop_back();
                op->right = r;
                op->left = l;
                stack.push_back(op);
                j++;
                continue;
            }
        }
        else if ((int((code[j])[0] - '0') >= 0 && int((code[j])[0] - '0') <= 9) || (int((code[j])[0]) == int('-') && int((code[j])[1] - '0') >= 0 && int((code[j])[1] - '0') <= 9)){
            UnlimitedInt* lala = new UnlimitedInt(code[j]);
            ExprTreeNode* node = new ExprTreeNode("VAL", lala);
            delete lala;
            stack.push_back(node);
            j++;
            continue;
        }
        else{
            ExprTreeNode* node = new ExprTreeNode("VAR", this->symtable->search(code[j]));
            node->id = code[j];
            stack.push_back(node);
            j++;
            continue;
        }
    }
    root->right = stack.back();
    stack.pop_back();
    this->expr_trees.push_back(root);
    delete brack_open;
}

void call(Evaluator* clss, ExprTreeNode* ptr){
    if (ptr->left == NULL && ptr->right == NULL){
        return;
    }
    else{
        call(clss, ptr->right);
        call(clss, ptr->left);
        if (ptr->type.compare("ADD") == 0){
            ptr->evaluated_value = UnlimitedRational::add(ptr->left->evaluated_value, ptr->right->evaluated_value);
        }
        else if (ptr->type.compare("SUB") == 0){
            ptr->evaluated_value = UnlimitedRational::sub(ptr->left->evaluated_value, ptr->right->evaluated_value);
        }
        else if (ptr->type.compare("MUL") == 0){
            ptr->evaluated_value = UnlimitedRational::mul(ptr->left->evaluated_value, ptr->right->evaluated_value);
        }
        else if (ptr->type.compare("DIV") == 0){
            ptr->evaluated_value = UnlimitedRational::div(ptr->left->evaluated_value, ptr->right->evaluated_value);
        }
    }
}

void Evaluator::eval(){
    if (expr_trees.size() == 0){
        return;
    }
    ExprTreeNode* tree = expr_trees.back();
    call(this, tree->right);
    tree->left->evaluated_value = tree->right->evaluated_value;
    this->symtable->insert(tree->left->id, tree->left->evaluated_value);
}