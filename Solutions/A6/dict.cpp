// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here
    obj = Chaining();
    for(int i = 0; i < 35;i++)
    {
        pref[i] = -1;
    }
    for(int i = 35;i < 128;i++)
    {
        pref[i] = 0;
    }
    pref[39] = -1;
    pref[40] = -1;
    pref[41] = -1;
    pref[44] = -1;
    pref[45] = -1;
    pref[46] = -1;
    pref[58] = -1;
    pref[59] = -1;
    pref[63] = -1;
    pref[64] = -1;
    pref[91] = -1;
    pref[93] = -1;
    pref[127] = -1;

}

Dict::~Dict(){
    // Implement your function here
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    string curr="";
    for(char i:sentence){
        int a=tolower(i);
        i=a;
        if (pref[i]==-1){
            if(curr!=""){
                int hash_val = obj.hash(curr);
                obj.bankStorage2d[hash_val]->insert(curr);
            }
            curr="";

        }
        else{
            curr +=i;
        }

    }
    if (curr!=""){
        int hash_val = obj.hash(curr);
        obj.bankStorage2d[hash_val]->insert(curr);
    }
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here
    int n = word.size();
    for(int i = 0; i < n;i++)
    {
        int z = tolower(word[i]);
        word[i] = z;
    }
    return obj.getBalance(word);
}

void call(fstream &fh, Dict::SymNode* node){
    fh << node->key << ", " << node->address <<"\n";
    if (node->left != NULL){
        call(fh, node->left);
    }
    if (node->right != NULL){
        call(fh, node->right);
    }
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    fstream file_handle;
    file_handle.open(filename, std::ios::out);
    for (int i = 0; i < 10007; i++){
        if (obj.bankStorage2d[i]->root != NULL){
            call(file_handle, obj.bankStorage2d[i]->root);
        }
    }
    file_handle.close();
    return;
}