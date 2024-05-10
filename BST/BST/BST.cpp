#include <iostream>

using namespace std;

class Node {
private:
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    int data;
public:
    Node(int data) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
    }
    Node* getParent() {
        return parent;
    }
    Node* getLeftChild() {
        return leftChild;
    }
    Node* getRightChild() {
        return rightChild;
    }
    int getData() {
        return data;
    }
    void setParent(Node* parent) {
        this->parent = parent;
    }

    void setLeftChild(Node* leftChild) {
        this->leftChild = leftChild;
    }

    void setRightChild(Node* rightChild) {
        this->rightChild = rightChild;
    }

    void setData(int data) {
        this->data = data;
    }
};

class BST
{
private:
    Node* root;

public:
    BST(int data) {
        root = new Node(data);
    }

    Node* getRoot() {
        return root;
    }

    void setRoot(Node* newRoot) {
        root = newRoot;
    }

    ~BST() {
        deleteSubtree(root);
    }

    void deleteSubtree(Node* node) {
        if (node != nullptr) {
            deleteSubtree(node->getLeftChild());
            deleteSubtree(node->getRightChild());
            delete node;
        }
    }

    void inOrderTreeWalk(Node* node) {
        if (node != nullptr) {
            inOrderTreeWalk(node->getLeftChild());
            cout << node->getData() << " ";
            inOrderTreeWalk(node->getRightChild());
        }
    }

    void print() {
        inOrderTreeWalk(root);
    }

    void insert(int key) {
        Node* newNode = new Node(key);
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (key < current->getData()) {
                current = current->getLeftChild();
            }
            else {
                current = current->getRightChild();
            }
        }

        newNode->setParent(parent);

        if (parent == nullptr) {
            root = newNode;
        }
        else if (key < parent->getData()) {
            parent->setLeftChild(newNode);
        }
        else {
            parent->setRightChild(newNode);
        }
    }

    Node* search(int key) {
        Node* current = root;

        while (current != nullptr && current->getData() != key) {
            if (key < current->getData()) {
                current = current->getLeftChild();
            }
            else {
                current = current->getRightChild();
            }
        }

        return current;
    }

    Node* minimum(Node* node) {
        while (node->getLeftChild() != nullptr) {
            node = node->getLeftChild();
        }
        return node;
    }

    Node* successor(Node* node) {
        if (node->getRightChild() != nullptr) {
            return minimum(node->getRightChild());
        }

        Node* parent = node->getParent();
        while (parent != nullptr && node == parent->getRightChild()) {
            node = parent;
            parent = parent->getParent();
        }
        return parent;
    }

    void transplant(Node* u, Node* v) {
        if (u->getParent() == nullptr) {
            root = v;
        }
        else if (u == u->getParent()->getLeftChild()) {
            u->getParent()->setLeftChild(v);
        }
        else {
            u->getParent()->setRightChild(v);
        }
        if (v != nullptr) {
            v->setParent(u->getParent());
        }
    }

    void deleteNode(int key) {
        Node* nodeToDelete = search(key);
        if (nodeToDelete == nullptr) {
            return;
        }
        if (nodeToDelete->getLeftChild() == nullptr) {
            transplant(nodeToDelete, nodeToDelete->getRightChild());
        }
        else if (nodeToDelete->getRightChild() == nullptr) {
            transplant(nodeToDelete, nodeToDelete->getLeftChild());
        }
        else {
            Node* successorNode = minimum(nodeToDelete->getRightChild());
            if (successorNode->getParent() != nodeToDelete) {
                transplant(successorNode, successorNode->getRightChild());
                successorNode->setRightChild(nodeToDelete->getRightChild());
                successorNode->getRightChild()->setParent(successorNode);
            }
            transplant(nodeToDelete, successorNode);
            successorNode->setLeftChild(nodeToDelete->getLeftChild());
            successorNode->getLeftChild()->setParent(successorNode);
        }
        delete nodeToDelete;
    }
};

int main()
{
    BST tree1(7);
    tree1.insert(9);
    tree1.insert(4);
    tree1.insert(2);
    tree1.insert(6);
    tree1.insert(8);
    tree1.insert(10);

    cout << "In-order traversal before deletion: ";
    tree1.print();
    cout << endl;

    tree1.deleteNode(4);

    cout << "In-order traversal after deletion: ";
    tree1.print();
    cout << endl;

    return 0;
}
