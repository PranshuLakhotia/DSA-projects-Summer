#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    Chaining(){
        bankStorage2d.reserve(1009);
    }
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int binary_search(std::string id);
    std::vector<Account> merge(std::vector<Account> &vec, int idx2, int k);
    int bin_ser(std::vector<int> &vec, int ele);
    int hash_table_size = 0;
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
