#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

using namespace std ; 
int main()
{
    map <string,int> obj;
    obj["apple"] = 10;
    obj["banana"] = 2;
    obj["kiwi"] = 9;

    // cout << obj["apple"] << endl;
    obj.insert({"pineapple",13});
    for (const auto & pair : obj)
    {
        // cout << pair.first << ": " << pair.second << std::endl;
    }

    map<int, int> obj1;
    vector<int> a= {1,3,5,7,4,8};


    for(int i =0;i<6;i++){
        obj1[a[i]]+=1;
    }

    for(const auto & it:obj1){
        // cout << "key :" << it.first << " value: " << it.second << endl;
    }

    map<int,int> test;
    
    test[10];
    cout << test[10] << endl;



    return 0;
}