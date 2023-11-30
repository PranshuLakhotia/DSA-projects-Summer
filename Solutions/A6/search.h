// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine {
private:
    // You can add attributes/helper functions here

public:
    class pr{
        public :
            int info[4];
            string sentence;
            pr(int book_code, int page, int paragraph, int sentence_no, string sentence)
            {
                *info = book_code;
                *(info+1) =  page;
                *(info+2) =  paragraph;
                *(info+3) = sentence_no;
                this->sentence = sentence;
                int n = this->sentence.size();
                for(int i = 0; i < n;i++)
                {
                    int z = tolower(this->sentence[i]);
                    this->sentence[i] = z;
                }
            }
    };
    vector<pr> data;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};