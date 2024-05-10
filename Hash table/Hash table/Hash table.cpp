#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string key;
    Node* next;
    Node* prev;

    Node(string key) {
        this->key = key;
        next = nullptr;
        prev = nullptr;
    }
};

class HashTable {
private:
    Node** hashArr;
    int x;

    unsigned long long hash(string& str) {
        unsigned long long hashValue = 0;

        for (char c : str) {
            hashValue = hashValue * 128 + c;
        }
        return hashValue;
    }


public:
    HashTable(int x) {
        this->x = x;
        this->hashArr = new Node * [x];

        for (int i = 0; i < x; ++i) {
            hashArr[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < x; ++i) {
            Node* current = hashArr[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] hashArr;
    }

    void HashInsert(string str) {
        unsigned long long hashedValue = hash(str);
        int index = hashedValue % x;
        Node* newNode = new Node(str);
        if (hashArr[index] == nullptr) {
            hashArr[index] = newNode;
        }
        else {
            Node* current = hashArr[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }


    void HashDelete(string str) {
        unsigned long long hashedValue = hash(str);
        int index = hashedValue % x;
        Node* current = hashArr[index];

        while (current != nullptr) {
            if (current->key == str) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                else {
                    hashArr[index] = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }

                delete current;
                return;
            }
            current = current->next;
        }

        cout << "not found for deletion" << endl;
    }

     void HashSearch(string str) {
        unsigned long long hashedValue = hash(str);
        Node* current = hashArr[hashedValue % x];
        int i = 0;

        while (current != nullptr) {
            if (current->key == str) {
                cout << "[" << hashedValue % x << "]" << "[" << i << "]" << endl;
                return;
            }
            i++;
            current = current->next;
        }
        cout << "not found" << endl;
    }
};


int main() {
    HashTable hashTable(7);

    hashTable.HashInsert("apple");
    hashTable.HashInsert("banana");
    hashTable.HashInsert("cat");
    hashTable.HashInsert("cook");
    hashTable.HashInsert("dog");

    cout << "Searching for 'apple': ";
    hashTable.HashSearch("apple");
    cout << endl;

    cout << "Searching for 'banana': ";
    hashTable.HashSearch("banana");
    cout << endl;

    cout << "Searching for 'cat': ";
    hashTable.HashSearch("cat");
    cout << endl;

    cout << "Searching for 'cook': ";
    hashTable.HashSearch("cook");
    cout << endl;

    cout << "Searching for 'dog': ";
    hashTable.HashSearch("dog");
    cout << endl;

    hashTable.HashDelete("banana");

    cout << "Searching for 'banana' after deletion: ";
    hashTable.HashSearch("banana");
    cout << endl;
    return 0;
}
