/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
using namespace std;

UnlimitedInt* gcd(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* i3 = new UnlimitedInt(0);
    UnlimitedInt* i4 = new UnlimitedInt(0);
    int *arr3 = new int[i1->get_size()];
    int*arr4 = new int[i2->get_size()];
    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    for (int i = 0; i < int(i1->get_size()); i++){
        arr3[i] = arr1[i];
    }
    for (int i = 0; i < int(i2->get_size()); i++){
        arr4[i] = arr2[i];
    }
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign();
    delete i3;
    delete i4;
    i3 = new UnlimitedInt(arr3, i1->get_capacity(), 1, i1->get_size());
    i4 = new UnlimitedInt(arr4, i2->get_capacity(), 1, i2->get_size());
    delete[] arr3;
    delete[] arr4;
    UnlimitedInt* diff = UnlimitedInt::sub(i3, i4);
    if (diff->get_sign() == 0){
        delete diff;
        delete i3;
        delete i4;
        return new UnlimitedInt(i1->to_string());
    }
    else if (diff->get_sign() == -1){
        delete diff;
        return gcd(i2, i1);
    }
    // UnlimitedInt* div = UnlimitedInt::div(i3, i4);
    UnlimitedInt* rem = UnlimitedInt::mod(i3, i4);
    while (rem->get_sign() != 0){
        delete i3;
        i3 = i4;
        i4 = rem;
        // div = UnlimitedInt::div(i3, i4);
        rem = UnlimitedInt::mod(i3, i4);
    }
    delete i3;
    delete diff;
    delete rem;
    return i4;
}

UnlimitedRational::UnlimitedRational(){
    delete this->p;
    delete this->q;
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    this->p = num;
    this->q = den;
    UnlimitedInt* g = gcd(p, q);
    this->p = UnlimitedInt::div(p, g);
    this->q = UnlimitedInt::div(q, g);
    delete g;
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return this->p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return this->q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    string s1 = p->to_string();
    string s2 = q->to_string();
    return s1 + "/" + s2;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    if ((i1->q->get_sign() == 0) || (i2->q->get_sign() == 0)){
        UnlimitedInt* a = new UnlimitedInt(0);
        UnlimitedInt* b = new UnlimitedInt(0);
        UnlimitedRational* ans = new UnlimitedRational(a, b);
        delete a;
        delete b;
        return ans;
    }
    UnlimitedInt* one = UnlimitedInt::mul(i1->p, i2->q);
    UnlimitedInt* two = UnlimitedInt::mul(i1->q, i2->p);
    UnlimitedInt* three = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedInt* four = UnlimitedInt::add(one, two);
    delete one;
    delete two;
    UnlimitedRational* ans = new UnlimitedRational(four, three);
    delete three;
    delete four;
    return ans;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    if ((i1->q->get_sign() == 0) || (i2->q->get_sign() == 0)){
        UnlimitedInt* a = new UnlimitedInt(0);
        UnlimitedInt* b = new UnlimitedInt(0);
        UnlimitedRational* ans = new UnlimitedRational(a, b);
        delete a;
        delete b;
        return ans;
    }
    UnlimitedInt* one = UnlimitedInt::mul(i1->p, i2->p);
    UnlimitedInt* two = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedRational* ans = new UnlimitedRational(one, two);
    delete one;
    delete two;
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    if ((i1->q->get_sign() == 0) || (i2->q->get_sign() == 0)){
        UnlimitedInt* a = new UnlimitedInt(0);
        UnlimitedInt* b = new UnlimitedInt(0);
        UnlimitedRational* ans = new UnlimitedRational(a, b);
        delete a;
        delete b;
        return ans;
    }
    UnlimitedInt* one = UnlimitedInt::mul(i1->p, i2->q);
    UnlimitedInt* two = UnlimitedInt::mul(i1->q, i2->p);
    UnlimitedInt* three = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedInt* four = UnlimitedInt::sub(one, two);
    delete one;
    delete two;
    UnlimitedRational* ans = new UnlimitedRational(four, three);
    delete three;
    delete four;
    return ans;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    if ((i1->q->get_sign() == 0) || (i2->p->get_sign() == 0)){
        UnlimitedInt* a = new UnlimitedInt(0);
        UnlimitedInt* b = new UnlimitedInt(0);
        UnlimitedRational* ans = new UnlimitedRational(a, b);
        delete a;
        delete b;
        return ans;
    }
    UnlimitedInt* one = UnlimitedInt::mul(i1->p, i2->q);
    UnlimitedInt* two = UnlimitedInt::mul(i1->q, i2->p);
    UnlimitedRational* ans = new UnlimitedRational(one, two);
    delete one;
    delete two;
    return ans;
}