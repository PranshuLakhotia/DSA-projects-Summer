/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}

int call(SymbolTable* symtable, ExprTreeNode* ptr){
    if (ptr->left != NULL){
        int a = call(symtable, ptr->right);
        int b = call(symtable, ptr->left);
        if (ptr->type.compare("ADD") == 0){
            if (a == NULL || b == NULL){
                return NULL;
            }
            return a + b;
        }
        else if (ptr->type.compare("SUB") == 0){
            if (a == NULL || b == NULL){
                return NULL;
            }
            return b - a;
        }
        else if (ptr->type.compare("MUL") == 0){
            if (a == NULL || b == NULL){
                return NULL;
            }
            return a * b;
        }
        else if (ptr->type.compare("DIV") == 0){
            if (a == 0 || a == NULL || b == NULL){
                return NULL;
            }
            return b / a;
        }
    }
    else{
        return ptr->num;
    }
}

void Parser::parse(vector<string> code){
    vector<ExprTreeNode*> stack;
    ExprTreeNode* root = new ExprTreeNode();

    root->left = new ExprTreeNode();
    if (code[0].compare("del") == 0){
        root->left->type = "DEL";
        root->left->id = "DEL";
    }
    else if (code[0].compare("ret") == 0){
        root->left->type = "RET";
        root->left->id = "RET";
    }
    else{
        root->left->id = code[0];
        root->left->type = "VAR";
    }

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
            ExprTreeNode* node = new ExprTreeNode("VAL", stoi(code[j]));
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

    // updating symtable

    if (code[0].compare("del") == 0){
        this->symtable->remove(root->right->id);
    }
    else if (root->left->type.compare("VAR") == 0){
        int evaluated_value = call(this->symtable, root->right);
        root->left->num = evaluated_value;
        this->symtable->insert(root->left->id);
    }
}

Parser::~Parser(){
    delete symtable;
    int a = expr_trees.size();
    for (int i = 0; i < a; i++){
        ExprTreeNode* x = expr_trees.back();
        expr_trees.pop_back();
        delete x;
    }
}