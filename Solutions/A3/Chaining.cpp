#include "Chaining.h"

int Chaining::binary_search(std::string id){
    int hash_val = hash(id);
    int lo = 0;
    int hi = (bankStorage2d[hash_val]).size() - 1;
    int mid, cmp;
    while (lo <= hi){
        if (lo == hi){
            cmp = (bankStorage2d[hash_val][lo].id).compare(id);
            if (cmp <= 0){
                return lo;
            }
            else{
                return -1;
            }
        }
        mid = (lo + hi)/2;
        cmp = (bankStorage2d[hash_val][mid].id).compare(id);
        if (cmp <= 0){
            cmp = (bankStorage2d[hash_val][mid+1].id).compare(id);
            if (cmp > 0){
                return mid;
            }
            else{
                lo = mid+1;
            }
        }
        else{
            hi = mid;
        }
    }
    return -1;
}

void Chaining::createAccount(std::string id, int count) {
    int hash_val = hash(id);
    Account acc;
    acc.id = id;
    acc.balance = count;
    int idx = this->binary_search(id);
    (bankStorage2d[hash_val]).insert((bankStorage2d[hash_val]).begin() + idx + 1, acc);
    // (bankStorage2d[hash_val]).push_back(acc);
    hash_table_size++;
    return;
}

std::vector<Account> Chaining::merge(std::vector<Account> &vec, int idx2, int k){
    std::vector<Account> res;
    for (int i = 0; i < k; i++){
        Account temp;
        temp.id = "NA";
        temp.balance = 0;
        res.push_back(temp);
    }
    int cnt = 0;
    int n1 = vec.size();
    int n2 = (bankStorage2d[idx2]).size();
    int k1 = n1 - 1, k2 = n2 - 1, k3 = k - 1;
    while (cnt != k && (k1 >=0 && k2 >= 0)){
        if (vec[k1].balance > bankStorage2d[idx2][k2].balance){
            res[k3] = vec[k1];
            cnt++;
            k3--;
            k1--;
        }
        else{
            res[k3] = bankStorage2d[idx2][k2];
            cnt++;
            k3--;
            k2--;
        }
    }
    while(cnt != k && k2 >= 0){
        res[k3] = bankStorage2d[idx2][k2];
        cnt++;
        k3--;
        k2--;
    }
    while (cnt != k && k1 >= 0){
        res[k3] = vec[k1];
        cnt++;
        k3--;
        k1--;
    }
    return res;
}

int Chaining::bin_ser(std::vector<int> &vec, int ele){
    int lo = 0;
    int hi = vec.size() - 1;
    int mid;
    if (hi == -1){
        return 0;
    }
    while (lo <= hi){
        if (lo == hi){
            if (vec[lo] <= ele){
                return lo;
            }
            else{
                return lo+1;
            }
        }
        mid = (lo + hi)/2;
        if (vec[mid + 1] <= ele){
            if (vec[mid] > ele){
                return mid + 1;
            }
            else{
                hi = mid;
            }
        }
        else{
            lo = mid+1;
        }
    }
    return -1;
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> res;
    int n = 0;
    // std::vector<Account> final_merged = bankStorage2d[0];
    for (int i = 0; i < 1009; i++){
        // final_merged = merge(final_merged, i, k);
        for (int j = 0; j < bankStorage2d[i].size(); j++){
            int idx = bin_ser(res, bankStorage2d[i][j].balance);
            res.insert(res.begin() + idx, bankStorage2d[i][j].balance);
            if (n == k){
                res.pop_back();
            }
            else{
                n++;
            }
        }
    }
    // for (int i = 0; i < k; i++){
    //     if (final_merged[i].id != "NA"){
    //         res.push_back(final_merged[i].balance);
    //     }
    // }
    // int y = 0, z = res.size()-1;
    // while (y < z){
    //     std::swap(res[y],res[z]);
    //     y++;
    //     z--;
    // }
    return res;
}

int Chaining::getBalance(std::string id) {
    int hash_val = hash(id);
    int idx = binary_search(id);
    if (idx == -1 || (bankStorage2d[hash_val][idx]).id != id){
        return -1;  // Placeholder return value
    }
    return (bankStorage2d[hash_val][idx]).balance;
}

void Chaining::addTransaction(std::string id, int count) {
    int hash_val = hash(id);
    int idx = binary_search(id);
    if (idx == -1 || (bankStorage2d[hash_val][idx]).id != id){
        Account acc;
        acc.id = id;
        acc.balance = count;
        (bankStorage2d[hash_val]).insert((bankStorage2d[hash_val]).begin() + idx + 1, acc);
        hash_table_size++;
        return;
    }
    (bankStorage2d[hash_val][idx]).balance += count;
    return;
    
}

bool Chaining::doesExist(std::string id) {
    int hash_val = hash(id);
    int idx = binary_search(id);
    if (idx == -1 || (bankStorage2d[hash_val][idx]).id != id){
        return false;  // Placeholder return value
    }
    return true;
}

bool Chaining::deleteAccount(std::string id) {
    int hash_val = hash(id);
    int idx = binary_search(id);
    if (idx == -1 || (bankStorage2d[hash_val][idx]).id != id){
        return false;  // Placeholder return value
    }
    (bankStorage2d[hash_val]).erase((bankStorage2d[hash_val]).begin() + idx);
    hash_table_size--;
    return true;
}
int Chaining::databaseSize() {
    return hash_table_size;
}

int Chaining::hash(std::string id) {
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
    return ((a + b + c)%1009);
}