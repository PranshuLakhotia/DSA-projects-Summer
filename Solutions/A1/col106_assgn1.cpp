#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

//template <typename T> 
class SET{
    private:
        vector<vector<int>*> arr;
    public:

        void insert(int num, int ele){
            if (arr.size() <= num){
                vector<int>* s = new vector<int>;
                (*s).push_back(ele);
                arr.push_back(s);
                cout<<"1"<<endl;
            }
            else{
                int idx = find(num, ele);
                if ((*arr[num])[idx] == ele){
                
                }
                else if (idx >= 0 and (*arr[num])[idx] < ele){
                    (*arr[num]).insert((*arr[num]).begin() + idx + 1, ele);
                }
                else {
                    (*arr[num]).insert((*arr[num]).begin() + 0, ele);
                }
                cout<<sizeof((*arr[num]))/sizeof((*arr[num])[0])<<endl;
            }
        }

        int find(int num, int ele){
            int start = 0;
            int end = (*arr[num]).size()/sizeof(int);
            while (true){
                if (start == end){
                    if ((*arr[num])[start] <= (ele)){
                        return start;
                    }
                    else{
                        return -1;
                    }
                }
                int mid = (start + end)/2;
                if ((*arr[num])[mid] <= (ele) and (*arr[num])[mid+1] > (ele)){
                    return mid;
                }
                else if ((*arr[num])[mid] > (ele)){
                    end = mid;
                    continue;
                }
                else{
                    start = mid + 1;
                    continue;
                }
            }
        }
        
        void del(int num, int ele){
            if (arr.size() <= num){
                cout<<"-1"<<endl;
            }
            else{
                int idx = find(num, ele);
                if (idx == -1 or (*arr[num])[idx] < ele){
                }
                else{
                    (*arr[num]).erase((*arr[num]).begin() + idx);
                }
                cout<<sizeof((*arr[num]))/sizeof((*arr[num])[0])<<endl;
            }
        }

        void belongsto(int num, int ele){
            if (arr.size() <= num){
                cout<<"-1"<<endl;
                return;
            }
            else{
                int start = 0;
                int end = sizeof(*arr[num])/sizeof((*arr[num])[0]);
                while (true){
                    if (start == end){
                        if ((*arr[num])[start] == (ele)){
                            cout<<"1"<<endl;
                            return;
                        }
                        else{
                            cout<<"0"<<endl;
                            return;
                        }
                    }
                    int mid = (start + end)/2;
                    if ((*arr[num])[mid] == (ele)){
                        cout<<"1"<<endl;
                        return;
                    }
                    else if ((*arr[num])[mid] > (ele)){
                        end = mid;
                        continue;
                    }
                    else{
                        start = mid + 1;
                        continue;
                    }
                }
            }
        }

        void Union(int num1, int num2){
            if (arr.size() <= num1 and arr.size() > num2){
                vector<int>* s1 = new vector<int>;
                *s1 = {};
                arr.push_back(s1);
                }
            else if (arr.size() <= num2 and arr.size() > num1){
                vector<int>* s2 = new vector<int>;
                *s2 = {};
                arr.push_back(s2);
            }
            else if (arr.size() <= num2 and arr.size() <= num1){
                vector<int>* s1 = new vector<int>;
                *s1 = {};
                vector<int>* s2 = new vector<int>;
                *s2 = {};
                if (num1 <= num2){
                    arr.push_back(s1);
                    arr.push_back(s2);
                }
                else{
                    arr.push_back(s2);
                    arr.push_back(s1);
                }
            }
            int l1 = (*arr[num1]).size();
            int l2 = (*arr[num2]).size();
            vector<int>* res = new vector<int>;
            int k1 = 0, k2 = 0; 
            while (k1 < l1 and k2 < l2){
                if ((*arr[num1])[k1] > (*arr[num2])[k2]){
                    (*res).push_back((*arr[num2])[k2]);
                    k2++;
                }
                else if ((*arr[num1])[k1] < (*arr[num2])[k2]){
                    (*res).push_back((*arr[num1])[k1]);
                    k1++;
                }
                else{
                    (*res).push_back((*arr[num2])[k2]);
                    k1++;
                    k2++;
                }
            }
            while (k1<l1){
                (*res).push_back((*arr[num1])[k1]);
                k1++;
            }
            while (k2<l2){
                (*res).push_back((*arr[num2])[k2]);
                k2++;
            }
            delete arr[num1];
            arr[num1] = res;
            cout<<(*res).size()<<endl;
            return;
        }

        void intersection(int num1, int num2){
            if (arr.size() <= num1 and arr.size() > num2){
                vector<int>* s1 = new vector<int>;
                *s1 = {};
                arr.push_back(s1);
                }
            else if (arr.size() <= num2 and arr.size() > num1){
                vector<int>* s2 = new vector<int>;
                *s2 = {};
                arr.push_back(s2);
            }
            else if (arr.size() <= num2 and arr.size() <= num1){
                vector<int>* s1 = new vector<int>;
                *s1 = {};
                vector<int>* s2 = new vector<int>;
                *s2 = {};
                if (num1 <= num2){
                    arr.push_back(s1);
                    arr.push_back(s2);
                }
                else{
                    arr.push_back(s2);
                    arr.push_back(s1);
                }
            }
            int l1 = (*arr[num1]).size();
            int l2 = (*arr[num2]).size();
            vector<int>* res = new vector<int>;
            int k1 = 0, k2 = 0; 
            while (k1 < l1 and k2 < l2){
                if ((*arr[num1])[k1] > (*arr[num2])[k2]){
                    k2++;
                }
                else if ((*arr[num1])[k1] < (*arr[num2])[k2]){
                    k1++;
                }
                else{
                    (*res).push_back((*arr[num2])[k2]);
                    k1++;
                    k2++;
                }
            }
            delete arr[num1];
            arr[num1] = res;
            cout<<(*res).size()<<endl;
            return;
        }

        void size(int num){
            cout<<(*arr[num]).size()<<endl;
            return;
        }

        void difference(int num1, int num2){
            if (arr.size() <= num1 and arr.size() > num2){
                vector<int>* s1 = new vector<int>;
                *s1 = {};
                arr.push_back(s1);
                }
            else if (arr.size() <= num2 and arr.size() > num1){
                vector<int>* s2 = new vector<int>;
                *s2 = {};
                arr.push_back(s2);
            }
            else if (arr.size() <= num2 and arr.size() <= num1){
                vector<int>* s1 = new vector<int>;
                *s1 = {};
                vector<int>* s2 = new vector<int>;
                *s2 = {};
                if (num1 <= num2){
                    arr.push_back(s1);
                    arr.push_back(s2);
                }
                else{
                    arr.push_back(s2);
                    arr.push_back(s1);
                }
            }

            int l1 = (*arr[num1]).size();
            int l2 = (*arr[num2]).size();
            vector<int>* res = new vector<int>;
            int k1 = 0, k2 = 0; 
            while (k1 < l1 and k2 < l2){
                if ((*arr[num1])[k1] > (*arr[num2])[k2]){
                    (*res).push_back((*arr[num1])[k1]);

                    while ((*arr[num1])[k1] >= (*arr[num2])[k2]){
                        k2++;
                    }
                    k1++;
                }
                else if ((*arr[num1])[k1] < (*arr[num2])[k2]){
                    (*res).push_back((*arr[num1])[k1]);
                    k1++;
                }
                else{
                    k1++;
                    k2++;
                }
            }
            while (k1<l1){
                (*res).push_back((*arr[num1])[k1]);
                k1++;
            }
            delete arr[num1];
            arr[num1] = res;
            cout<<(*res).size()<<endl;
            return;
        }

        void symmetric_difference(int num1, int num2){
            if (arr.size() <= num1 and arr.size() > num2){
                vector<int>* s1 = new vector<int>;
                *s1 = {};
                arr.push_back(s1);
                }
            else if (arr.size() <= num2 and arr.size() > num1){
                vector<int>* s2 = new vector<int>;
                *s2 = {};
                arr.push_back(s2);
            }
            else if (arr.size() <= num2 and arr.size() <= num1){
                vector<int>* s1 = new vector<int>;
                *s1 = {};
                vector<int>* s2 = new vector<int>;
                *s2 = {};
                if (num1 <= num2){
                    arr.push_back(s1);
                    arr.push_back(s2);
                }
                else{
                    arr.push_back(s2);
                    arr.push_back(s1);
                }
            }

            int l1 = (*arr[num1]).size();
            int l2 = (*arr[num2]).size();
            vector<int>* un = new vector<int>;
            vector<int>* inter = new vector<int>;
            vector<int>* res = new vector<int>;

            int k1 = 0, k2 = 0; 
            while (k1 < l1 and k2 < l2){
                if ((*arr[num1])[k1] > (*arr[num2])[k2]){
                    (*un).push_back((*arr[num2])[k2]);
                    k2++;
                }
                else if ((*arr[num1])[k1] < (*arr[num2])[k2]){
                    (*un).push_back((*arr[num1])[k1]);
                    k1++;
                }
                else{
                    (*un).push_back((*arr[num2])[k2]);
                    k1++;
                    k2++;
                }
            }
            while (k1<l1){
                (*un).push_back((*arr[num1])[k1]);
                k1++;
            }
            while (k2<l2){
                (*un).push_back((*arr[num2])[k2]);
                k2++;
            }

            k1 = 0;k2 = 0;
            while (k1 < l1 and k2 < l2){
                if ((*arr[num1])[k1] > (*arr[num2])[k2]){
                    k2++;
                }
                else if ((*arr[num1])[k1] < (*arr[num2])[k2]){
                    k1++;
                }
                else{
                    (*inter).push_back((*arr[num2])[k2]);
                    k1++;
                    k2++;
                }
            }

            k1 = 0;k2 = 0;
            l1 = (*un).size();
            l2 = (*inter).size();
            while (k1 < l1 and k2 < l2){
                if ((*un)[k1] > (*inter)[k2]){
                    (*res).push_back((*un)[k1]);

                    while ((*un)[k1] >= (*inter)[k2]){
                        k2++;
                    }
                    k1++;
                }
                else if ((*un)[k1] < (*inter)[k2]){
                    (*res).push_back((*un)[k1]);
                    k1++;
                }
                else{
                    k1++;
                    k2++;
                }
            }
            while (k1<l1){
                (*res).push_back((*un)[k1]);
                k1++;
            }

            delete arr[num1];
            arr[num1] = res;
            cout<<(*res).size()<<endl;
        }

        void print(int num){
            if (arr.size() <= num){
                cout<<"/n";
                return;
            }
            for (int i = 0; i < (*arr[num]).size(); i++){
                cout<<(*arr[num])[i]<<",";
            }
            cout<<endl;
            return;
        }

        ~SET(){
            for (int i = 0; i < arr.size(); i++){
                delete arr[i];
            }
        }

};

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    SET obj;
    int cmd;
    int num1, num2;
    while (cin>>cmd) {
        switch (cmd){
            case 1:
                cin>>num1>>num2;
                obj.insert(num1, num2);
                break;
            case 2:
                cin>>num1>>num2;
                obj.del(num1, num2);
                break;
            case 3:
                cin>>num1>>num2;
                obj.belongsto(num1, num2);
                break;
            case 4:
                cin>>num1>>num2;
                obj.Union(num1, num2);
                break;
            case 5:
                cin>>num1>>num2;
                obj.intersection(num1, num2);
                break;
            case 6:
                cin>>num1;
                obj.size(num1);
                break;
            case 7:
                cin>>num1>>num2;
                obj.difference(num1, num2);
                break;
            case 8:
                cin>>num1>>num2;
                obj.symmetric_difference(num1, num2);
                break;
            case 9:
                cin>>num1;
                obj.print(num1);
                break;
        }
    }
}
