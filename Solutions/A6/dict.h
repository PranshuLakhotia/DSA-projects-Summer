// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict {
private:
    // You can add attributes/helper functions here

public:
int pref[128];
class SymNode {
public:
    string key;
    int height;
    int address=1;

    SymNode* par;
    SymNode* left;
    SymNode* right;
SymNode(string k)
{
    this->key = k;
    this->height = 0;
    this->address = 1;
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
}

~SymNode()
{
    if (this->left != NULL)
    {
        delete this->left;
    }
    if (this->right != NULL)
    {
        delete this->right;
    }
}
};
class SymbolTable {
public:
    SymNode* root = NULL;

SymbolTable(){
    this->root = NULL;
}

int h(SymNode* node)
{
    if(node == NULL)
    {
        return -1;
    }
    return node->height;
}

SymNode* Left(SymNode* root, SymNode* ptr)
{
    SymNode* temp = ptr->right;
    temp->par = ptr->par;
    ptr->right = temp->left;
    if(ptr->right != NULL)
    {
        ptr->right->par = ptr;
    }
    temp->left = ptr;
    if(temp->par == NULL)
    {
        root = temp;
    }
    else
    {
        if(ptr->par->left == ptr)
        {
            ptr->par->left = temp;
        }
        else
        {
            ptr->par->right = temp;
        }
    }
    ptr->par = temp;
    ptr->height = 1 + std::max(h(ptr->right),h(ptr->left));
    temp->height = 1 + std::max(h(temp->right),h(temp->left));
    return root;
}

SymNode* Right(SymNode* root,SymNode* ptr)
{
    SymNode* temp = ptr->left;
    temp->par = ptr->par;
    ptr->left = temp->right;
    if(ptr->left != NULL)
    {
        ptr->left->par = ptr;
    }
    temp->right = ptr;
    if(temp->par == NULL)
    {
        root = temp;
    }
    else
    {
        if(ptr->par->left == ptr)
        {
            ptr->par->left = temp;
        }
        else
        {
            ptr->par->right = temp;
        }
    }
    ptr->par = temp;
    ptr->height = 1 + std::max(h(ptr->right),h(ptr->left));
    temp->height = 1 + std::max(h(temp->right),h(temp->left));
    return root;
}

void insert(string k){
    if(root == NULL)
    {
        SymNode* ins = new SymNode(k);
        root = ins;
        return;
    }
    SymNode* parent = NULL;
    SymNode* ptr = root;
    while(ptr != NULL)
    {
        if(ptr->key > k)
        {
            parent = ptr;
            ptr = ptr->left;
        }
        else if(ptr->key < k)
        {
            parent = ptr;
            ptr = ptr->right;
        }
        else
        {
            ptr->address++;
            return;
        }
    }
    SymNode* ins = new SymNode(k);
    if(parent->key > k)
    {
        parent->left = ins;
        ins->par = parent;
    }
    else
    {
        parent->right = ins;
        ins->par = parent;
    }
    while(parent != NULL)
    {
        parent->height = 1 + std::max(h(parent->left),h(parent->right));
        if(h(parent->left) > 1 + h(parent->right))
        {
            if(h(parent->left->right) > h(parent->left->left))
            {
                this->root = Left(this->root,parent->left);
            }
            this->root = Right(this->root,parent);
        }
        else if(h(parent->right) > 1 + h(parent->left))
        {
            if(h(parent->right->right) < h(parent->right->left))
            {
                this->root=Right(this->root,parent->right);
            }
            this->root = Left(this->root,parent);
        }
        parent = parent->par;
    }
    return;
}

SymNode* search(string k){
    SymNode* ptr = this->root;
    while(ptr != NULL)
    {
        if(ptr->key > k)
        {
            ptr = ptr->left;
        }
        else if(ptr->key < k)
        {
            ptr = ptr->right;
        }
        else
        {
            return ptr;
        }
    }
    return NULL;
}

~SymbolTable(){
    if(this->root != NULL)
    {
        delete this->root;
    }
}
};
class Chaining {
public:
    std::vector<SymbolTable*> bankStorage2d;
    Chaining(){
        bankStorage2d.reserve(10007);
        for (int i = 0; i < 10007; i++){
            bankStorage2d[i] = new SymbolTable();
        }
    }

    ~Chaining()
    {
        for(int i = 0; i < 10007;i++)
        {
            delete this->bankStorage2d[i];
        }
    }
    // Other data members and functions specific to Chaining

int getBalance(std::string id) {
    int hash_val = hash(id);
    SymNode* x = bankStorage2d[hash_val]->search(id);
    if (!x){
        return 0;
    }
    return x->address;
}

// hash only works for 22 length strings, modify it -- done somewhat!
int hash(std::string id) {
    // return 0;
    if(id == "")
    {
        return 0;
    }
    int x = 71;
    int a = 9901;
    int b = 8101;
    int h = 0;
    int n = id.size();
    int m = 10007;
    for(int i = 0; i < n;i++)
    {
        h = (h*x)%m;
        h += int(id[i]);
        h %= m;
    }
    int ans = (a*h)%m;
    ans = (ans + b)%m;
    ans = abs(ans);
    return ans;
}

};
    Chaining obj;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};