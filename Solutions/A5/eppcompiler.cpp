/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
//Write your code below this line

void heapifyup(vector<int> &vec, int idx){
    int par_idx = (idx - 1) / 2;
    if (par_idx < 0){
        return;
    }
    if (vec[par_idx] > vec[idx]){
        swap(vec[par_idx], vec[idx]);
        heapifyup(vec, par_idx);
    }
}

void heapifydown(vector<int> &vec, int idx){
    int lchild = 2*idx + 1;
    int rchild = 2*idx + 2;
    if (lchild > int(vec.size())){
        return;
    }
    int swapu = -1;
    if (vec[lchild] < vec[idx]){
        swapu = lchild;
    }
    if (rchild < int(vec.size()) && vec[rchild] < vec[idx] && vec[rchild] < vec[lchild]){
        swapu = rchild;
    }
    if (swapu == -1){
        return;
    }
    swap(vec[idx], vec[swapu]);
    heapifydown(vec, swapu);
}

void delmin(vector<int> &vec){
    vec[0] = vec[vec.size() - 1];
    vec.pop_back();
    heapifydown(vec, 0);
}

void heap_insert(vector<int> & vec, int num){
    vec.push_back(num);
    heapifyup(vec, int(vec.size()) - 1);
}

EPPCompiler::EPPCompiler(){
    memory_size = 128;  //default mem_limit
    output_file = "yahan_hai_output.txt";
    for (int i = 0; i < memory_size; i++){
        // mem_loc.push_back(i);
        least_mem_loc.push_heap(i);
    }
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit){
    memory_size = mem_limit;
    output_file = out_file;
    for (int i = 0; i < memory_size; i++){
        // mem_loc.push_back(i);
        least_mem_loc.push_heap(i);
    }
}

void gen_targ(vector<string> &res, ExprTreeNode* ptr, SymbolTable* sym){
    ExprTreeNode* ptrl = ptr->left;
    ExprTreeNode* ptrr = ptr->right;
    if (ptrl == NULL){
        if (ptr->type.compare("VAL") == 0){
            res.push_back("PUSH " + to_string(ptr->num));
        }
        else{
            res.push_back("PUSH mem[" + to_string(sym->search(ptr->id)) + "]");
        }
    }
    else{
        res.push_back(ptr->type);
        gen_targ(res, ptrl, sym);
        gen_targ(res, ptrr, sym);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    vector<string> targ_commands;
    for (int i = 0; i < int(code.size()); i++){
        if (code[i][0].compare("del") == 0){
            int addr = targ.symtable->search(code[i][2]);
            // heap_insert(mem_loc, addr);
            least_mem_loc.push_heap(addr);
            targ.parse(code[i]);
            targ.last_deleted = addr;
            targ_commands.push_back("DEL = mem[" + to_string(addr) + "]");
        }
        else if (code[i][0].compare("ret") == 0){
            targ.parse(code[i]);
            vector<string> comm;
            comm.push_back("RET = POP");
            ExprTreeNode* node = targ.expr_trees.back();
            gen_targ(comm, node->right, targ.symtable);
            for (int j = int(comm.size()) - 1; j >= 0; j--){
                targ_commands.push_back(comm[j]);
            }
            break;
        }
        else{
            //VAR case
            int addr = targ.symtable->search(code[i][0]);
            if (addr != -2){
                targ.parse(code[i]);
            }
            else{
                targ.parse(code[i]);
                // addr = mem_loc[0];
                addr = least_mem_loc.get_min();
                // delmin(mem_loc);
                least_mem_loc.pop();
                targ.symtable->assign_address(targ.expr_trees[i]->left->id, addr);
            }
            vector<string> comm;
            comm.push_back("mem[" + to_string(addr) + "] = POP");
            ExprTreeNode* node = targ.expr_trees.back();
            gen_targ(comm, node->right, targ.symtable);
            for (int j = int(comm.size()) - 1; j >= 0; j--){
                targ_commands.push_back(comm[j]);
            }
        }
    }

    //write targ commmands to output file
    this->write_to_file(targ_commands);
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* root = targ.expr_trees.back();
    vector<string> comm;
    if (root->left->type.compare("DEL") == 0){
        comm.push_back("DEL mem[" + to_string(targ.last_deleted) + "]");
    }
    else if (root->left->type.compare("RET") == 0){
        comm.push_back("RET = POP");
        gen_targ(comm, root->right, targ.symtable);
        int i = 0, j = int(comm.size()) - 1;
        while (i < j){
            swap(comm[i], comm[j]);
            i++;
            j--;
        }
    }
    else{
        //VAR case
        int addr = targ.symtable->search(root->left->id);
        comm.push_back("mem[" + to_string(addr) + "] = POP");
        gen_targ(comm, root->right, targ.symtable);
        int i = 0, j = int(comm.size()) - 1;
        while (i < j){
            swap(comm[i], comm[j]);
            i++;
            j--;
        }
    }
    return comm;
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream file_handle;
    file_handle.open(output_file, std::ios::out);
    for (int i = 0; i < int(commands.size()); i++){
        file_handle << commands[i] <<"\n";
    }
    file_handle.close();
}

EPPCompiler::~EPPCompiler(){}
#include <iostream>
int main()
{
    EPPCompiler x = EPPCompiler("hehe.txt", 4);
    vector<vector<string>> vec{{"x",":=","3"},{"y",":=","5"},{"z",":=","7"},{"del",":=","x"},{"w",":=","2"},{ "del" , ":=" , "y"},{"w",":=","(","5","+","(","z","/","2",")",")"}};
    x.compile(vec);
    fstream file;
    file.open("hehe.txt", std::ios::in);
    string line;
    while (std::getline(file, line))
    {
        std::cout << line << "\n";
    }
    return 0;

}