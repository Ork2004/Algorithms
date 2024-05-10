#include <iostream>

using namespace std;

class Node {
private:
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    int data;
    bool isRed;
public:
    Node(int data) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
        isRed = true;
    }
    Node* getParent() {
        return parent;
    }

    void setParent(Node* parent) {
        this->parent = parent;
    }

    Node* getLeftChild() {
        return leftChild;
    }

    void setLeftChild(Node* leftChild) {
        this->leftChild = leftChild;
    }

    Node* getRightChild() {
        return rightChild;
    }

    void setRightChild(Node* rightChild) {
        this->rightChild = rightChild;
    }

    int getData() {
        return data;
    }

    void setData(int data) {
        this->data = data;
    }

    bool getIsRed() {
        return isRed;
    }

    void setIsRed(bool isRed) {
        this->isRed = isRed;
    }
};

class redBlackTree {
private:
    Node* root;
public:
    redBlackTree(int data) {
        root = new Node(data);
    }

    Node* getRoot() {
        return root;
    }

    void setRoot(Node* newRoot) {
        root = newRoot;
        root->setIsRed(false);
    }

    ~redBlackTree() {
        deleteSubtree(root);
    }

    void deleteSubtree(Node* node) {
        if (node != nullptr) {
            deleteSubtree(node->getLeftChild());
            deleteSubtree(node->getRightChild());
            delete node;
        }
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

        if (parent == nullptr)
            root = newNode;
        else if (key < parent->getData())
            parent->setLeftChild(newNode);
        else
            parent->setRightChild(newNode);
        newNode->setLeftChild(nullptr);
        newNode->setRightChild(nullptr);
        newNode->setIsRed(true);
        insertFixup(newNode);
    }

    void leftRotate(Node* x) {
        Node* y = x->getRightChild();
        x->setRightChild(y->getLeftChild());
        if (y->getLeftChild() != nullptr)
            y->getLeftChild()->setParent(x);
        y->setParent(x->getParent());
        if (x->getParent() == nullptr)
            root = y;
        else if (x == x->getParent()->getLeftChild())
            x->getParent()->setLeftChild(y);
        else
            x->getParent()->setRightChild(y);
        y->setLeftChild(x);
        x->setParent(y);
    }

    void rightRotate(Node* x) {
        Node* y = x->getLeftChild();
        x->setLeftChild(y->getRightChild());
        if (y->getRightChild() != nullptr)
            y->getRightChild()->setParent(x);
        y->setParent(x->getParent());
        if (x->getParent() == nullptr)
            root = y;
        else if (x == x->getParent()->getRightChild())
            x->getParent()->setRightChild(y);
        else
            x->getParent()->setLeftChild(y);
        y->setRightChild(x);
        x->setParent(y);
    }

    void insertFixup(Node* newNode) {
        while (newNode != root && newNode->getParent()->getIsRed()) {
            if (newNode->getParent() == newNode->getParent()->getParent()->getLeftChild()) {
                Node* y = newNode->getParent()->getParent()->getRightChild();
                if (y != nullptr && y->getIsRed()) {
                    newNode->getParent()->setIsRed(false);
                    y->setIsRed(false);
                    newNode->getParent()->getParent()->setIsRed(true);
                    newNode = newNode->getParent()->getParent();
                }
                else {
                    if (newNode == newNode->getParent()->getRightChild()) {
                        newNode = newNode->getParent();
                        leftRotate(newNode);
                    }
                    newNode->getParent()->setIsRed(false);
                    newNode->getParent()->getParent()->setIsRed(true);
                    rightRotate(newNode->getParent()->getParent());
                }
            }
            else {
                Node* y = newNode->getParent()->getParent()->getLeftChild();
                if (y != nullptr && y->getIsRed()) {
                    newNode->getParent()->setIsRed(false);
                    y->setIsRed(false);
                    newNode->getParent()->getParent()->setIsRed(true);
                    newNode = newNode->getParent()->getParent();
                }
                else {
                    if (newNode == newNode->getParent()->getLeftChild()) {
                        newNode = newNode->getParent();
                        rightRotate(newNode);
                    }
                    newNode->getParent()->setIsRed(false);
                    newNode->getParent()->getParent()->setIsRed(true);
                    leftRotate(newNode->getParent()->getParent());
                }
            }
        }
        root->setIsRed(false);
    }

};

int main()
{
    redBlackTree RBT(7);
    RBT.insert(9);
    RBT.insert(4);
    RBT.insert(2);
    RBT.insert(6);
    RBT.insert(8);
    RBT.insert(10);



    return 0;
}
