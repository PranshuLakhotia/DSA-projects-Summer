#include "QuadraticProbing.h"
#include<iostream>

void QuadraticProbing::createAccount(std::string id, int count) {
    Account acc;
    acc.id = id;
    acc.balance = count;
    if (float(hash_table_size)/float(capacity) >= 0.5){
        // Dynamic resizing hash table
        long long j;
        std::vector<Account> vec(2 * capacity);
        capacity *= 2;
        for (int z = 0; z < (capacity / 2); z++){
            if (bankStorage1d[z].id.size() == 22){
                long long temp_hash_val = hash(bankStorage1d[z].id);
                j = 0;
                while (vec[(temp_hash_val + ((j * (j+1))/2))%capacity].id.size() == 22){
                    j++;
                }
                vec[(temp_hash_val + ((j * (j+1))/2))%capacity] = bankStorage1d[z];
            }
        }
        bankStorage1d = vec;
    }
    long long hash_val = hash(id);
    long long i = 0;
    while (bankStorage1d[(hash_val + ((i * (i+1))/2))%capacity].id.size() == 22){
        i++;
    }
    bankStorage1d[(hash_val + ((i * (i+1))/2))%capacity] = acc;
    hash_table_size++;
    return;
}

int QuadraticProbing::binary_search(std::vector<int> &res, int &val, int &cnt){
    int lo = 0;
    int hi = cnt - 1;
    int mid;
    if (cnt == 0){
        return 0;
    }
    while (lo <= hi){
        if (lo == hi){
            if (res[lo] <= val){
                return lo;
            }
            else{
                return -1;
            }
        }
        else{
            mid = (lo + hi)/2;
            if (res[mid + 1] <= val){
                if (res[mid] > val){
                    return mid + 1;
                }
                else{
                    hi = mid;
                }
            }
            else{
                lo = mid + 1;
            }
        }
    }
    return -1;
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    //std::cout<<"function starts\n";
    std::vector<int> res;     // res is reverse sorted
    int cnt = 0;
    for (int i = 0; i < capacity; i++){
        if (bankStorage1d[i].id.size() == 22){
            // std::cout<<bankStorage1d[i].balance<<"\n";
            int idx = this->binary_search(res, bankStorage1d[i].balance, cnt);
            if (idx == -1 and cnt != k){
                res.push_back(bankStorage1d[i].balance);
                cnt++;
                continue;
            }
            if (idx == -1 and cnt == k){
                continue;
            }
            res.insert(res.begin() + idx, bankStorage1d[i].balance);
            if (cnt == k){
                res.pop_back();
            }
            else{
                cnt++;
            }
        }
    }
    //std::cout<<"function ends\n";
    return res;
}

int QuadraticProbing::getBalance(std::string id) {
    long long hash_val = hash(id);
    int i = 0;
    long long p;
    while (i < capacity){
        p = ((i * (i+1))/2);
        if (bankStorage1d[(hash_val + p)%capacity].id == "!"){
            i++;
            continue;
        }
        else if (bankStorage1d[(hash_val + p)%capacity].id.size() == 22){
            if (bankStorage1d[(hash_val + p)%capacity].id == id){
                return bankStorage1d[(hash_val + p)%capacity].balance;
            }
            else{
                i++;
                continue;
            }
        }
        else{
            return -1;
        }
    }
    return -1;
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    long long hash_val = hash(id);
    int i = 0;
    long long p;
    while (i < capacity){
        p  =((i * (i+1))/2);
        if (bankStorage1d[(hash_val + p)%capacity].id == "!"){
            i++;
            continue;
        }
        else if (bankStorage1d[(hash_val + p)%capacity].id.size() == 22){
            if (bankStorage1d[(hash_val + p)%capacity].id == id){
                bankStorage1d[(hash_val + p)%capacity].balance += count;
                return;
            }
            else{
                i++;
                continue;
            }
        }
        else{
            this->createAccount(id, count);
            return;
        }
    }
    this->createAccount(id, count);
    return;
}

bool QuadraticProbing::doesExist(std::string id) {
    long long hash_val = hash(id);
    int i = 0;
    long long p;
    while (i < capacity){
        p = ((i * (i+1))/2);
        if (bankStorage1d[(hash_val + p)%capacity].id == "!"){
            i++;
            continue;
        }
        else if (bankStorage1d[(hash_val + p)%capacity].id.size() == 22){
            if (bankStorage1d[(hash_val + p)%capacity].id == id){
                return true;
            }
            else{
                i++;
                continue;
            }
        }
        else{
            return false;
        }
    }
    return false;
}

bool QuadraticProbing::deleteAccount(std::string id) {
    long long hash_val = hash(id);
    int i = 0;
    long long p;
    bool res, x = 0;
    while (i < capacity){
        p = ((i * (i+1))/2);
        if (bankStorage1d[(hash_val + p)%capacity].id == "!"){
            i++;
            continue;
        }
        else if (bankStorage1d[(hash_val + p)%capacity].id.size() == 22){
            if (bankStorage1d[(hash_val + p)%capacity].id == id){
                bankStorage1d[(hash_val + p)%capacity].id = "!";
                bankStorage1d[(hash_val + p)%capacity].balance = 0;
                hash_table_size--;
                res = true;
                x = 1;
                break;
            }
            else{
                i++;
                continue;
            }
        }
        else{
            res = false;
            x = 1;
            break;
        }
    }
    if (x == 0){
        res = false;
    }
    //checking if the table is too empty and resizing
    if (float(hash_table_size)/float(capacity) <= 0.125){
        std::vector<Account> vec(capacity / 2);
        int old_capacity = capacity;
        capacity /= 2;
        long long j;
        for (int z = 0; z < old_capacity; z++){
            if (bankStorage1d[z].id.size() == 22){
                long long temp_hash_val = hash(bankStorage1d[z].id);
                j = 0;
                while (vec[(temp_hash_val + ((j * (j+1))/2))%capacity].id.size() == 22){
                    j++;
                }
                vec[(temp_hash_val + ((j * (j+1))/2))%capacity] = bankStorage1d[z];
            }
        }
        bankStorage1d = vec;
    }
    return res;
}

int QuadraticProbing::databaseSize() {
    return hash_table_size;
}

int QuadraticProbing::hash(std::string id) {
    uint32_t h0 = 0b01100111110111100010101000000001;
    uint32_t h1 = 0b10111011000000111110001010001100;
    uint32_t h2 = 0b00000001000111101111000111011100;
    uint32_t var[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 22; i++){
        var[i/4] = var[i/4]<<8;
        var[i/4] += uint8_t(id[i]);
    }
    var[5]<<16;
    var[7] += 176;
    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t arr[40];
    for (int j = 0; j<8; j++){
        arr[j] = var[j];
    }
    for (int j = 8; j < 40; j++){
        arr[j] = arr[j-1] ^ (arr[j-3]<<2) ^ arr[j-5] ^ arr[j-8];
        arr[j] = arr[j]<<2;
    }
    for (int j = 0; j < 40; j++){
        uint32_t temp = (a>>2) + ((b+c)>>(j%7)) + arr[j];
        c = b;
        b = a;
        a = temp;
    }
    a = (h0 + a);
    b = (h1 + b);
    c = (h2 + c);
    return ((a + b + c)%capacity);
}