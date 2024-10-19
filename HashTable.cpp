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

// Function to find the next prime number greater than or equal to n
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
    vector<int> table; // The hash table (stores keys)

    // Hash function: h(k) = k % m
    int hash(int key) {
        return key % m;
    }

    // Resize the table when load factor exceeds threshold
    void resize() {
        int new_m = newprime(2 * m); // New size should be a prime number
        vector<int> newTable(new_m, -1); // Initialize new table

        // Rehash all existing elements into the new table
        for (int i = 0; i < m; i++) {
            if (table[i] != -1) { // Only rehash non-empty elements
                int newIndex = table[i] % new_m;
                int j = 0;
                while (newTable[(newIndex + j * j) % new_m] != -1) {
                    j++;
                }
                newTable[(newIndex + j * j) % new_m] = table[i];
            }
        }

        table = newTable; // Replace old table with the new one
        m = new_m; // Update the table size
    }

public:
    // Constructor to initialize the hash table with a prime size
    HashTable(int size) {
        m = newprime(size); // Adjust size to the nearest prime number
        table.resize(m, -1); // Initialize the table with -1 (indicating empty)
        alpha = 0.8;
        n = 0;
    }

    // Insert function
    void insert(int key) {
        float allah = m*alpha;
        if (n >= allah) {
            resize();
        }

        int index = hash(key);
        int j = 0;

        while (j < m) {
            int newIndex = (index + j * j) % m;

            // Check if the key already exists
            if (table[newIndex] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return; 
            }

            // If we find an empty slot, insert the key
            if (table[newIndex] == -1) {
                table[newIndex] = key; // Insert key
                n++; // Increment the count of elements
                return;
            }
            j++;
        }

        cout << "Max probing limit reached!" << endl; // This will print if you exhaust all probing attempts
    }

    // Search function
    int search(int key) {
        int index = hash(key);
        int j = 0;

        // Quadratic probing to search
        while (j < m) {
            int newIndex = (index + j * j) % m;
            if (table[newIndex] == key) {
                return newIndex; // Return the index if key is found
            }
            if (table[newIndex] == -1) {
                return -1; // Return -1 if key is not found
            }
            j++;
        }
        return -1; // Return -1 if key is not found after full probing
    }

    // Remove function
    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            cout << "Element not found" << endl;
        } else {
            table[index] = -1; // Mark the slot as empty
            n--; // Decrease the number of elements
        }
    }

    // Print the current state of the hash table
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
