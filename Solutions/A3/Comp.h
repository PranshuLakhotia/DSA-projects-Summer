#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    Comp(){
        bankStorage1d.reserve(512);
        capacity = 512;
        hash_table_size = 0;
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
    int binary_search(std::vector<int> &res, int &val, int &cnt);
    int hash_table_size;
    int capacity;
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
