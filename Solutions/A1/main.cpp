#include <iostream>
#include <vector>

using namespace std;

class SET{
    public:
        vector<int> arr = {};
        void insert(int ele){
            if (arr.size() == 0){
                arr.push_back(ele);
                cout<<"1"<<endl;
                return;
            }
            int idx = find(ele);
            if (idx != -1 and arr[idx] == ele){}
            else {
                arr.insert(arr.begin() + idx + 1, ele);
            }
            cout<<arr.size()<<endl;
        }

        int find(int ele){
            int start = 0;
            int end = arr.size() - 1;
            while (true){
                if (start == end or end == -1){       
                    if (end != -1 and arr[start] <= (ele)){
                        return start;
                    }
                    else{
                        return -1;
                    }
                }
                int mid = (start + end)/2;
                if (arr[mid] <= (ele) and arr[mid+1] > (ele)){
                    return mid;
                }
                else if (arr[mid] > (ele)){
                    end = mid;
                    continue;
                }
                else{
                    start = mid + 1;
                    continue;
                }
            }
        }
        
        void del(int ele){
                int idx = find(ele);
                if (idx != -1 and arr[idx] == ele){
                    arr.erase(arr.begin() + idx);
                }
                cout<<arr.size()<<endl;
        }

        void belongsto(int ele){
                int start = 0;
                int end = arr.size() - 1;
                if (arr.size() == 0){
                    cout<<"0"<<endl;
                    return;
                }
                while (true){
                    if (start == end){
                        if (arr[start] == ele){
                            cout<<"1"<<endl;
                            return;
                        }
                        else{
                            cout<<"0"<<endl;
                            return;
                        }
                    }
                    int mid = (start + end)/2;
                    if (arr[mid] == ele){
                        cout<<"1"<<endl;
                        return;
                    }
                    else if (arr[mid] > ele){
                        end = mid;
                        continue;
                    }
                    else{
                        start = mid + 1;
                        continue;
                    }
                }
        }

        void Union(SET other){
            int l1 = arr.size();
            int l2 = other.arr.size();
            vector<int> res;
            int k1 = 0, k2 = 0; 
            while (k1 < l1 and k2 < l2){
                if (arr[k1] > (other.arr)[k2]){
                    res.push_back((other.arr)[k2]);
                    k2++;
                }
                else if (arr[k1] < (other.arr)[k2]){
                    res.push_back(arr[k1]);
                    k1++;
                }
                else{
                    res.push_back(arr[k1]);
                    k1++;
                    k2++;
                }
            }
            while (k1<l1){
                res.push_back(arr[k1]);
                k1++;
            }
            while (k2<l2){
                res.push_back((other.arr)[k2]);
                k2++;
            }
            arr = res;
            cout<<arr.size()<<endl;
        }

        void intersection(SET &other){
            int l1 = arr.size();
            int l2 = other.arr.size();
            vector<int> res;
            int k1 = 0, k2 = 0; 
            while (k1 < l1 and k2 < l2){
                if (arr[k1] > (other.arr)[k2]){
                    k2++;
                }
                else if (arr[k1] < (other.arr)[k2]){
                    k1++;
                }
                else{
                    res.push_back(arr[k1]);
                    k1++;
                    k2++;
                }
            }
            arr = res;
            cout<<arr.size()<<endl;
        }

        void size(){
            cout<<arr.size()<<endl;
        }

        void difference(SET &other){
            int l1 = arr.size();
            int l2 = other.arr.size();
            vector<int> res;
            int k1 = 0, k2 = 0; 
            while (k1 < l1 and k2 < l2){
                if (arr[k1] > (other.arr)[k2]){
                    k2++;
                }
                else if (arr[k1] < (other.arr)[k2]){
                    res.push_back(arr[k1]);
                    k1++;
                }
                else{
                    k1++;
                    k2++;
                }
            }
            while (k1<l1){
                res.push_back(arr[k1]);
                k1++;
            }
            arr = res;
            cout<<arr.size()<<endl;
        }

        void symmetric_difference(SET other){
            int l1 = arr.size();
            int l2 = other.arr.size();
            vector<int> res;

            int k1 = 0, k2 = 0; 
            while (k1 < l1 and k2 < l2){
                if (arr[k1] < (other.arr)[k2]){
                    res.push_back(arr[k1]);
                    k1++;
                }
                else if (arr[k1] > (other.arr)[k2]){
                    res.push_back((other.arr)[k2]);
                    k2++;
                }
                else{
                    k1++;
                    k2++;
                }
            }
            while(k1 < l1){
                res.push_back(arr[k1]);
                k1++;
            }
            while (k2 < l2){
                res.push_back((other.arr)[k2]);
                k2++;
            }

            arr = res;
            cout<<arr.size()<<endl;
        }

        void print(){
            if (arr.size() == 0){
                cout<<endl;
                return;
            }
            for (int i = 0; i < arr.size() - 1; i++){
                cout<<arr[i]<<",";
            }
            cout<<arr[arr.size() - 1]<<endl;
        }

};

int main(){

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    vector<SET> arr;
    int cmd, num1, num2;
    while (cin>>cmd) {
        switch (cmd){
            case 1:
                cin>>num1>>num2;
                if (arr.size() <= num1){
                    arr.push_back(SET());
                    arr[num1].insert(num2);
                }
                else{
                    (arr[num1]).insert(num2);
                }
                break;
            case 2:
                cin>>num1>>num2;
                if (arr.size() <= num1){
                    cout<<"-1"<<endl;
                }
                else{
                    (arr[num1]).del(num2);
                }
                break;
            case 3:
                cin>>num1>>num2;
                if (arr.size() <= num1){
                    cout<<"-1"<<endl;
                }
                else{
                    (arr[num1]).belongsto(num2);
                }
                break;
            case 4:
                cin>>num1>>num2;
                if (arr.size() <= num1 and arr.size() > num2){
                    arr.push_back(SET());
                    }
                else if (arr.size() <= num2 and arr.size() > num1){
                    arr.push_back(SET());
                }
                else if (arr.size() <= num2 and arr.size() <= num1){
                    if (num1 <= num2){
                        arr.push_back(SET());
                        arr.push_back(SET());
                    }
                    else{
                        arr.push_back(SET());
                        arr.push_back(SET());
                    }
                }
                (arr[num1]).Union(arr[num2]);
                break;
            case 5:
                cin>>num1>>num2;
                if (arr.size() <= num1 and arr.size() > num2){
                    arr.push_back(SET());
                    }
                else if (arr.size() <= num2 and arr.size() > num1){
                    arr.push_back(SET());
                }
                else if (arr.size() <= num2 and arr.size() <= num1){
                    if (num1 <= num2){
                        arr.push_back(SET());
                        arr.push_back(SET());
                    }
                    else{
                        arr.push_back(SET());
                        arr.push_back(SET());
                    }
                }
                (arr[num1]).intersection(arr[num2]);
                break;
            case 6:
                cin>>num1;
                if (arr.size() <= num1){
                    arr.push_back(SET());
                    cout<<"0"<<endl;
                }
                else{
                    (arr[num1]).size();
                }
                break;
            case 7:
                cin>>num1>>num2;
                if (arr.size() <= num1){
                    arr.push_back(SET());
                }
                if (arr.size() <= num2){
                    arr.push_back(SET());
                }
                (arr[num1]).difference(arr[num2]);
                break;
            case 8:
                cin>>num1>>num2;
                if (arr.size() <= num1 and arr.size() > num2){
                    arr.push_back(SET());
                    }
                else if (arr.size() <= num2 and arr.size() > num1){
                    arr.push_back(SET());
                }
                else if (arr.size() <= num2 and arr.size() <= num1){
                    if (num1 <= num2){
                        arr.push_back(SET());
                        arr.push_back(SET());
                    }
                    else{
                        arr.push_back(SET());
                        arr.push_back(SET());
                    }
                }
                (arr[num1]).symmetric_difference(arr[num2]);
                break;
            case 9:
                cin>>num1;
                if (arr.size() <= num1){
                    cout<<endl;
                }
                else{
                    (arr[num1]).print();
                }
                break;
            default:
                cout<<"Wrong Input"<<endl;
                break;
        }
    }
}
