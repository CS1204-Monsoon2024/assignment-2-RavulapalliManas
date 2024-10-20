#include <iostream>
#include <vector>
using namespace std;

// Function to check if a number is prime
bool isprime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to find the next prime number 
int newprime(int n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}

//class hashtable
class HashTable {
private:
    int n; 
    int m; 
    float alpha; 
    vector<int> table; 

    //hashfunction
    int hash(int key) {
        return key % m;
    }

    // Resizing the table
    void resize() {
        int new_m = newprime(2 * m); 
        vector<int> newTable(new_m, -1);
        for (int i = 0; i < m; i++) {
            if (table[i] != -1) { 
                int newIndex = table[i] % new_m;
                int j = 0;
                while (newTable[(newIndex + j * j) % new_m] != -1) {
                    j++;
                }
                newTable[(newIndex + j * j) % new_m] = table[i];
            }
        }

        table = newTable; 
        m = new_m; 
    }

public:
    //initializing the hash table
    HashTable(int size) {
        m = newprime(size); 
        table.resize(m, -1); 
        alpha = 0.8;
        n = 0;
    }

    // Insert function
    void insert(int key) {
        float load = m*alpha;
        if (n >= load) {
            resize();
        }

        int index = hash(key);
        int j = 0;

        while (j < m) {
            int newIndex = (index + j * j) % m;
            if (table[newIndex] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return; 
            }
            if (table[newIndex] == -1) {
                table[newIndex] = key;
                n++; 
                return;
            }
            j++;
        }
        cout << "Max probing limit reached!" << endl; 
    }

    // Search function
    int search(int key) {
        int index = hash(key);
        int j = 0;

        // Quadratic probing to search
        while (j < m) {
            int newIndex = (index + j * j) % m;
            if (table[newIndex] == key) {
                return newIndex; 
            }
            if (table[newIndex] == -1) {
                return -1; 
            }
            j++;
        }
        return -1; 
    }

    // Remove function
    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            cout << "Element not found" << endl;
        } else {
            table[index] = -1; 
            n--; 
        }
    }

    //print table function to print the ahsh table
    void printTable() {
        for (int i = 0; i < m; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
