#include<iostream>
#include<vector>
using namespace std;

//generate a prime number 
int isprime(int n){
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

//generate a prime number greater than n
int newprime(int n){
    while (!isprime(n)){
        n++;
    }
    return n;
}

class HashTable{
private:
    int n; //number of elements
    int m; //size of the array
    float alpha; //load factor
    vector<int> arr;

    //hashing function
    int hash(int key){
        return key % m;
    }
    //resing the table
    void resize(){
        int new_m = newprime(2*m);
        vector<int> newarr(new_m, -1);
        
        //inserting the elements into the new array
        for (int i = 0; i < m; i++){
            if (arr[i] != -1){
               int newindex = hash(arr[i], new_m);
               int j = 0;
               while(newarr[newindex] != -1){
                newindex = (hash(arr[i]) + j*j) % new_m;
                j++;
               }
               newarr[newindex] = arr[i];
            }
        }
        arr = newarr;
        m = new_m;
    }

public:
    HashTable(int size){
        m = newprime(size);
        arr.resize(m, -1);
        alpha = 0.8;
        n = 0;  

    }
    void insert(int key){
        if ((float)n/m > alpha){
            resize();
        }
        int index = hash(key);
        int j = 0;
        while(j<m){
            int newindex = (hash(key) + j*j) % m;
            if(arr[newindex] == key){
                cout << "Duplicate key insertion is not allowed" << endl;
                return -1;
            }
            else if(arr[newindex] == -1){
                arr[newindex] = key;
                n++;
                break;
            }
            j++;
        }
        cout << "Max probing limit reached!" << endl;
        return -1;
    }

    int search(int key){
        int index = hash(key);
        int j = 0;
        while(j<m){
            int newindex = (hash(key) + j*j) % m;
            if(arr[newindex] == key){
                return newindex;
            }
            else if(arr[newindex] == -1){
                cout << "Element not found" << endl;
                return -1;
            }
            j++;
        }
        cout << "Element not found" << endl;
        return -1;
    }

    void printTable() {
    for (int i = 0; i < size; i++) {
        if (arr[i] == -1) {
            std::cout << "- ";
        } else {
            std::cout << table[i] << " ";
        }
    }
    std::cout << "\n";
}

};


