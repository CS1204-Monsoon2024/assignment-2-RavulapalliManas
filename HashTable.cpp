#include <iostream>
#include <vector>
using namespace std;

// Check if a number is prime
bool isprime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Generate a prime number greater than n
int newprime(int n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}

class HashTable {
private:
    int n; // Number of elements in the table
    int m; // Size of the table
    float alpha; // Load factor threshold
    vector<int> keys; // Stores keys (initialized to -1 for empty slots)
    vector<int> values; // Stores values (initialized to -1 for empty slots)
    vector<bool> deleted; // Marks if a key has been deleted

    // Hashing function: h(k) = k % m
    int hash(int key) {
        return key % m;
    }

    // Resize and rehash the table when load factor exceeds alpha
    void resize() {
        int new_m = newprime(2 * m); // Find the new size (prime)
        vector<int> newKeys(new_m, -1);
        vector<int> newValues(new_m, -1);
        vector<bool> newDeleted(new_m, false);

        // Rehash all keys and values into the new table
        for (int i = 0; i < m; i++) {
            if (keys[i] != -1 && !deleted[i]) { // Rehash only valid keys
                int newindex = hash(keys[i]) % new_m;
                int j = 0;
                while (newKeys[(newindex + j * j) % new_m] != -1) {
                    j++;
                }
                newKeys[(newindex + j * j) % new_m] = keys[i];
                newValues[(newindex + j * j) % new_m] = values[i];
            }
        }
        keys = newKeys;
        values = newValues;
        deleted = newDeleted;
        m = new_m; // Update the size of the table
    }

public:
    HashTable(int size) {
        m = newprime(size);
        keys.resize(m, -1); // Initialize keys to -1 (empty)
        values.resize(m, -1); // Initialize values to -1 (empty)
        deleted.resize(m, false); // Initially, no key has been deleted
        alpha = 0.8;
        n = 0;
    }

    // Insert key-value pair into the hash table
    void insert(int key, int value) {
        if ((float)n / m > alpha) {
            resize(); // Resize if load factor exceeds alpha
        }

        int index = hash(key);
        int j = 0;
        while (j < m) {
            int newindex = (index + j * j) % m;
            if (keys[newindex] == key) {
                // Update value if key already exists
                values[newindex] = value;
                return;
            } else if (keys[newindex] == -1 || deleted[newindex]) {
                // Insert into the first available slot
                keys[newindex] = key;
                values[newindex] = value;
                deleted[newindex] = false;
                n++;
                return;
            }
            j++;
        }
        cout << "Max probing limit reached!" << endl;
    }

    // Search for a key and return its associated value
    int search(int key) {
        int index = hash(key);
        int j = 0;
        while (j < m) {
            int newindex = (index + j * j) % m;
            if (keys[newindex] == key && !deleted[newindex]) {
                return values[newindex];
            } else if (keys[newindex] == -1 && !deleted[newindex]) {
                cout << "Element not found" << endl;
                return -1;
            }
            j++;
        }
        cout << "Element not found" << endl;
        return -1;
    }

    // Delete a key from the hash table
    void remove(int key) {
        int index = hash(key);
        int j = 0;
        while (j < m) {
            int newindex = (index + j * j) % m;
            if (keys[newindex] == key && !deleted[newindex]) {
                deleted[newindex] = true; // Mark the key as deleted
                n--;
                return;
            } else if (keys[newindex] == -1 && !deleted[newindex]) {
                cout << "Key not found!" << endl;
                return;
            }
            j++;
        }
        cout << "Key not found!" << endl;
    }

    // Print the current state of the hash table
    void printTable() {
        for (int i = 0; i < m; i++) {
            if (keys[i] == -1 || deleted[i]) {
                cout << "- ";
            } else {
                cout << "(" << keys[i] << ", " << values[i] << ") ";
            }
        }
        cout << "\n";
    }
};
