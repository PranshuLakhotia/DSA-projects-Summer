// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine(){
    // Implement your function here
    data.clear();
}

SearchEngine::~SearchEngine(){
    // Implement your function here

}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    pr s = pr(book_code, page, paragraph, sentence_no, sentence);
    data.push_back(s);
    return;
}

void prefix_comp(string pattern, int* arr){
    *arr = 0;
    int k = 0;
    for (int q = 1; q < int(pattern.size()); q++){
        while (k > 0 && pattern[k] != pattern[q]){
            k = *(arr+k-1);
        }
        if (pattern[k] == pattern[q]){
            k++;
        }
        *(arr+q) = k;
    }
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here
    n_matches = 0;
    Node* root = NULL;
    int m = pattern.size();
    for(int i = 0; i < m;i++)
    {
        int z = tolower(pattern[i]);
        pattern[i] = z;
    }
    int pi[m];
    prefix_comp(pattern, pi);
    int x = data.size();
    for (int i = 0; i < x; i++){
        int n = data[i].sentence.size();
        int q = 0;                               // numbers of characters matched
        for (int j = 0; j < n; j++){
            while (q > 0 && pattern[q] != data[i].sentence[j]){
                q = *(pi+q-1);
            }
            if (pattern[q] == data[i].sentence[j]){
                q++;
            }
            if (q == m){
                Node* matched = new Node(*(data[i].info), *(data[i].info+1), *(data[i].info+2), *(data[i].info+3), j-q + 1);
                if (root){
                    root->left = matched;
                }
                matched->right = root;
                root = matched;
                root->left = NULL;
                n_matches++;
                q = *(pi+q-1);
            }
        }
    }
    return root;
}