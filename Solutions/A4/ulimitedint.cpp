/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include <string>
#include "ulimitedint.h"
using namespace std;

UnlimitedInt::UnlimitedInt(){
    size = 1;
    sign = 0;
    capacity = 1;
    this->unlimited_int = new int[capacity]();
    (*(this->unlimited_int)) = 0;
}
UnlimitedInt::UnlimitedInt(string s){
    if (s[0] == '-'){
        sign  = -1;
        size = int(s.size()) - 1;
        capacity = size;
        this->unlimited_int = new int[capacity]();
        for (int i = 1; i <= size; i++){
            *(this->unlimited_int + i - 1) = int(s[i] - '0');
        }
    }
    else {
        int i = 0;
        while (s[i] == '0'){
            i++;
        }
        if (i == int(s.size())){
            sign = 0;
            size = 1;
            capacity = 1;
            this->unlimited_int = new int[capacity]();
            (*(this->unlimited_int)) = 0;
        }
        else{
            size = int(s.size()) - i;
            capacity = size;
            sign = 1;
            this->unlimited_int = new int[capacity]();
            for (int j = i; j <int(s.size()); j++){
                this->unlimited_int[j-i] = int(s[j] - '0');
            }
        }
    }
}
UnlimitedInt::UnlimitedInt(int i){
    string s = std::to_string(i);
    if (s[0] == '-'){
        sign  = -1;
        size = int(s.size()) - 1;
        capacity = size;
        this->unlimited_int = new int[capacity]();
        for (int i = 1; i <= size; i++){
            *(this->unlimited_int + i - 1) = int(s[i] - '0');
        }
    }
    else {
        int i = 0;
        while (s[i] == '0'){
            i++;
        }
        if (i == int(s.size())){
            sign = 0;
            size = 1;
            capacity = 1;
            this->unlimited_int = new int[capacity]();
            (*(this->unlimited_int)) = 0;
        }
        else{
            size = int(s.size()) - i;
            capacity = size;
            sign = 1;
            this->unlimited_int = new int[capacity]();
            for (int j = i; j <int(s.size()); j++){
                this->unlimited_int[j-i] = int(s[j] - '0');
            }
        }
    }
}
UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    sign = sgn;
    size = sz;
    this->unlimited_int = new int[sz]();
    for(int i = sz - 1; i >= 0; i--)
    {
        this->unlimited_int[i] = ulimited_int[cap - sz + i];
    }
    capacity = size;
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

int UnlimitedInt::get_size(){
    return size;
}
int* UnlimitedInt::get_array(){
    return this->unlimited_int;
}
int UnlimitedInt::get_sign(){
    return sign;
}
int UnlimitedInt::get_capacity(){
    return capacity;
}
string UnlimitedInt::to_string(){
    string ans;
    if (this->sign == 0){
        return "0";
    }
    if (this->sign == -1){
        ans += '-';
    }
    for (int i = capacity - size; i < capacity; i++){
        ans += std::to_string(*(this->unlimited_int + i));
    }
    return ans;
}

void reverse(int* ptr, int n){
    int i = 0, j = n-1;
    while (i < j){
        swap(*(ptr + i), *(ptr + j));
        i++;
        j--;
    }
    return;
}

int comp(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->get_size() < i2->get_size()) {
        return -1;
    }
    else if (i1->get_size() > i2->get_size()) {
        return 1;
    }
    else {
        int *temp1=i1->get_array();
        int *temp2=i2->get_array();
        for (int i = 0; i < i1->get_size(); i++) {
            if (temp1[i] < temp2[i]) {
                return -1;
            } else if (temp1[i] > temp2[i]) {
                return 1;
            }
        }
        return 0;
    }
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* ek = UnlimitedInt::div(i1, i2);
    UnlimitedInt* doo = UnlimitedInt::mul(ek, i2);
    UnlimitedInt* ans = UnlimitedInt::sub(i1, doo);
    delete ek;
    delete doo;
    return ans;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->get_sign() == 0){
        UnlimitedInt* ans = new UnlimitedInt(i2->to_string());
        return ans;
    }
    if (i2->get_sign() == 0){
        UnlimitedInt* ans = new UnlimitedInt(i1->to_string());
        return ans;
    }

    int sgn1 = i1->get_sign(), sgn2 =i2->get_sign();
    int cap1 = i1->get_capacity(), cap2 = i2->get_capacity();
    int sz1 = i1->get_size(), sz2 = i2->get_size();
    int *ptr1 = i1->get_array(), *ptr2 = i2->get_array();

    if (sgn1 == sgn2){
        int *arr = new int[max(sz1, sz2) + 1];
        int maxi = sz1 > sz2 ? sz1 : sz2;
        for (int i = 0; i < maxi + 1; i ++){
            arr[i] = 0;
        }
        int mini = sz1 < sz2 ? sz1 : sz2;
        int i = sz1 - 1, j = sz2 - 1;
        int k = maxi;
        while (i >= 0 && j >= 0){
            arr[k] = ptr1[i] + ptr2[j];
            i--;
            j--;
            k--;
        }
        if (k >= 0){
            if (maxi == sz2){
                for (int k = maxi-mini-1; k >= 0; k--){
                    arr[k+1] = ptr2[k];
                }
            }
            else{
                for (int k = maxi-mini-1; k >= 0; k--){
                    arr[k+1] = ptr1[k];
                }
            }
        }
        for (int k = maxi; k >= 1; k--){
            arr[k-1] += arr[k]/10;
            arr[k] = arr[k]%10;
        }
        int var = 0;
        for (int z = 0; z <= maxi; z++){
            if (arr[z] != 0){
                var = z;
                break;
            }
        }
        UnlimitedInt* ans = new UnlimitedInt(arr, maxi + 1, sgn2, maxi + 1 - var);
        delete[] arr;
        return ans;
    }
    else{
        int c = comp(i1, i2);
        if (c == 0){
            UnlimitedInt* ans = new UnlimitedInt(0);
            return ans;
        }
        else{
            if (c == 1){
                int *arr = new int[sz1]();
                for (int i = 0; i < sz1; i++){
                    arr[i] = 0;
                }
                int i = sz1 - 1, j = sz2 - 1;
                int k = sz1 - 1;
                while (i >= 0 && j >= 0){
                    arr[k] = ptr1[i] - ptr2[j];
                    i--;
                    j--;
                    k--;
                }
                while (i >= 0){
                    arr[k] = ptr1[i];
                    k--;
                    i--;
                }
                for (int z = sz1 - 1; z >= 1; z--){
                    if (arr[z] < 0){
                        arr[z] += 10;
                        arr[z-1] --;
                    }
                }
                int var = 0;
                for(int z = 0; z < sz1; z++){
                    if (arr[z] != 0){
                        var = z;
                        break;
                    }
                }
                UnlimitedInt* ans = new UnlimitedInt(arr, sz1, sgn1, sz1 - var);
                delete[] arr;
                return ans;
            }
            else{
                int *arr = new int[sz2]();
                for (int i = 0; i < sz2; i++){
                    arr[i] = 0;
                }
                int i = sz1 - 1, j = sz2 - 1;
                int k = sz2 - 1;
                while (i >= 0 && j >= 0){
                    arr[k] = ptr2[j] - ptr1[i];
                    i--;
                    j--;
                    k--;
                }
                while (j >= 0){
                    arr[k] = ptr2[j];
                    k--;
                    j--;
                }
                for (int z = sz2 - 1; z >= 1; z--){
                    if (arr[z] < 0){
                        arr[z] += 10;
                        arr[z-1] --;
                    }
                }
                int var = 0;
                for(int z = 0; z < sz2; z++){
                    if (arr[z] != 0){
                        var = z;
                        break;
                    }
                }
                UnlimitedInt* ans = new UnlimitedInt(arr, sz2, sgn2, sz2 - var);
                delete[] arr;
                return ans;
            }
        }
    }
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    i2->sign *= -1;
    UnlimitedInt* ans = UnlimitedInt::add(i1, i2);
    i2->sign *= -1;
    return ans;
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->sign == 0 || i2->sign == 0){
        UnlimitedInt* ans = new UnlimitedInt(0);
        return ans;
    }
    int sz1 = i1->size, sz2 = i2->size;
    int* ptr1 = i1->get_array(), *ptr2 = i2->get_array();
    int* arr = new int[sz1 + sz2]();
    for (int k = 0; k < sz1 + sz2; k++){
        arr[k] = 0;
    }
    for (int i = 0; i < sz1; i++){
        for (int j = 0; j < sz2; j++){
            arr[i + j + 1] += ptr1[i] * ptr2[j];
        }
    }
    for (int k = sz1 + sz2 - 1; k > 0; k--){
        arr[k-1] += arr[k]/10;
        arr[k] = arr[k]%10;
    }
    int var=  0;
    for (int k = 0; k < sz1 + sz2; k++){
        if (arr[k] != 0){
            var = k;
            break;
        }
    }
    UnlimitedInt* ans = new UnlimitedInt(arr, sz1 + sz2, i1->get_sign() * i2->get_sign(), sz1 + sz2 - var);
    delete[] arr;
    return ans;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->sign == 0 || i2->sign == 0){
        return new UnlimitedInt(0);
    }
    int c = comp(i1, i2);
    if (c == 0){
        UnlimitedInt* ans = new UnlimitedInt(1);
        ans->sign = i1->sign * i2->sign;
        return ans;
    }
    else if (c == -1){
        if (i1->get_sign() != i2->get_sign()){
            return new UnlimitedInt(-1);
        }
        return new UnlimitedInt(0);
    }
    else{
        int sgn1 = i1->get_sign(), sgn2 =i2->get_sign();
        int sz1 = i1->get_size(), sz2 = i2->get_size();
        int *ptr1 = i1->get_array(), *ptr2 = i2->get_array();
        int *arr = new int[sz1]();
        UnlimitedInt* num = new UnlimitedInt(0);
        for (int i = 0; i < sz1; i++){
            int * new_num_arr = new int[num->size + 1]();
            int* num_arr = num->get_array();
            for (int j = 0; j < num->size; j++){
                new_num_arr[j] = num_arr[j];
            }
            new_num_arr[num->size] = ptr1[i];
            int nsz = num->size;
            int nsgn = num->sign;
            int ncap = nsz + 1;
            delete num;
            if (nsgn != 0){
                nsz += 1;
            }
            if (ptr1[i] != 0){
                nsgn = 1;
            }
            num = new UnlimitedInt(new_num_arr, ncap, nsgn, nsz);
            delete[] new_num_arr;
            for (int k = 1; k <= 10; k++){
                UnlimitedInt* n = new UnlimitedInt(k);
                UnlimitedInt* one = UnlimitedInt::mul(n, i2);
                delete n;
                UnlimitedInt* res = UnlimitedInt::sub(num, one);
                delete one;
                if (res->sign == -1){
                    arr[i] = k-1;
                    delete num;
                    num = UnlimitedInt::add(res, i2);
                    delete res;
                    break;
                }
                delete res;
            }
        }
        delete num;
        int var = 0;
        for (int i = 0; i < sz1; i++){
            if (arr[i] != 0){
                var = i;
                break;
            }
        }
        UnlimitedInt* ek = new UnlimitedInt(arr, sz1, 1, sz1 - var);
        delete[] arr;
        if (sgn1 == sgn2){
            return ek;
        }
        else{
            UnlimitedInt* doo = UnlimitedInt::mul(ek, i2);
            if (comp(doo, i1) == 0){
                ek->sign = -1;
                delete doo;
                return ek;
            }
            else{
                UnlimitedInt* o = new UnlimitedInt(1);
                UnlimitedInt* ans = UnlimitedInt::add(ek, o);
                delete o;
                delete ek;
                delete doo;
                ans->sign = -1;
                return ans;
            }
        }
    }
}

// int main()
// {
//     UnlimitedInt x("12345");
//     UnlimitedInt y("-9256765432");
//     UnlimitedInt* z = UnlimitedInt::mul(&y,&x);
//     cout << z->to_string() << endl;
//     delete z;
// }