#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    LinearProbing(){
        // 499 is prime
        bankStorage1d.reserve(499);
        capacity = 499;
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
    // int binary_search(std::vector<int> &res, int &val, int &cnt);
    
private:
    int hash_table_size;
    int capacity;
    // Other data members and functions specific to Linear Probing
};

#endif // LINEARPROBING_H
