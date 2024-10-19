#include<iostream>
#include<vector>
using namespace std;

int isprime(int n){
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int newprime(int n){
    while (!isprime(n)){
        n++;
    }
    return n;
}

class HashTable{
public:
    int n; //number of elements
    int m; //size of the array
    float alpha = 0.8; //load factor
    vector<int> arr;

    int hash(int key){
        return key % m;
    }

    void resize(){
        int newsize = newprime(2*m);
        vector<int> newarr(newsize, -1);
        for (int i = 0; i < m; i++){
            if (arr[i] != -1){
                int key = arr[i];
                int index = hash(key);
                newarr[index] = key;
            }
        }
        arr = newarr;
        m = newsize;
    }

    void insert(int key){
        if (n/m > alpha){
            resize();
        }
        int index = hash(key);
        arr[index] = key;
        n++;
    }

    void search(int key){
        int index = hash(key);
        if (arr[index] == key){
            cout << "Key found at index " << index << endl;
        }
        else{
            cout << "Key not found" << endl;
        }
    }

    void display(){
        for (int i = 0; i < m; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main(){

}
