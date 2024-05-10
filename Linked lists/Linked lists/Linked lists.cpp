#include <iostream>

class Node {
public:
    int key;
    Node* next;
    Node* prev;

    Node(int key) {
        this->key = key;
        next = nullptr;
        prev = nullptr;
    }
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~LinkedList() {
        Node* current = head;
        Node* next;
        while (current != nullptr) {
            next = current->next;
            deleteNode(current);
            current = next;
        }
    }

    void insertHead(int key) {
        Node* newNode = new Node(key);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insertTail(int key) {
        Node* newNode = new Node(key);
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void deleteNode(Node* x) {
        if (x == nullptr) {
            return;
        }
        if (x->next != nullptr) {
            x->next->prev = x->prev;
        }
        else {
            head = x->prev;
        }
        if (x->prev != nullptr) {
            x->prev->next = x->next;
        }
        delete x;
        size--;
    }

    void deleteNodeByIndex(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index\n";
            return;
        }

        Node* current = head;
        for (int i = 0; current != nullptr && i < index; i++) {
            current = current->next;
        }

        deleteNode(current);
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->key << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node* searcj(int data) {
        Node* current = head;
        while (current != nullptr) {
            if (current->key == data) return current;
            current = current->next;
        }
    }
};

int main() {
    LinkedList list;

    list.insertHead(5);
    list.insertTail(10);
    list.insertHead(15);
    list.insertTail(20);

    list.display();

    list.deleteNodeByIndex(2);

    list.display();

    return 0;
}
