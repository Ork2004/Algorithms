#include <iostream>
#include <queue>

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T data) : data(data), next(nullptr) {}
};

template<typename T>
class LinkedList {
public:
    Node<T>* head;
    LinkedList() : head(nullptr) {}

    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

template<typename T>
class Vertex {
public:
    T id;
    LinkedList<T> adjList;

    Vertex(T id) : id(id) {}
};

template<typename T>
class Graph {
public:
    LinkedList<Vertex<T>> vertices;

    void insert(Vertex<T> v) {
        vertices.pushBack(v);
    }

    void display() {
        Node<Vertex<T>>* temp = vertices.head;
        while (temp != nullptr) {
            std::cout << "Vertex " << temp->data.id << " is connected to: ";
            temp->data.adjList.display();
            temp = temp->next;
        }
    }

    void BFS(T startId) {
        bool* visited = new bool[verticesCount()]();
        std::queue<Vertex<T>> queue;

        visited[startId - 1] = true;

        Node<Vertex<T>>* temp = vertices.head;
        while (temp != nullptr && temp->data.id != startId) {
            temp = temp->next;
        }

        if (temp != nullptr) {
            queue.push(temp->data);
        }

        while (!queue.empty()) {
            Vertex<T> v = queue.front();
            std::cout << v.id << " ";
            queue.pop();

            Node<T>* adjNode = v.adjList.head;
            while (adjNode != nullptr) {
                if (!visited[adjNode->data - 1]) {
                    visited[adjNode->data - 1] = true;
                    Node<Vertex<T>>* temp = vertices.head;
                    while (temp != nullptr && temp->data.id != adjNode->data) {
                        temp = temp->next;
                    }
                    if (temp != nullptr) {
                        queue.push(temp->data);
                    }
                }
                adjNode = adjNode->next;
            }
        }

        delete[] visited;
    }

    void DFSUtil(Vertex<T> v, bool visited[]) {
        visited[v.id - 1] = true;
        std::cout << v.id << " ";

        Node<T>* adjNode = v.adjList.head;
        while (adjNode != nullptr) {
            if (!visited[adjNode->data - 1]) {
                Node<Vertex<T>>* temp = vertices.head;
                while (temp != nullptr && temp->data.id != adjNode->data) {
                    temp = temp->next;
                }
                if (temp != nullptr) {
                    DFSUtil(temp->data, visited);
                }
            }
            adjNode = adjNode->next;
        }
    }

    void DFS(T startId) {
        bool* visited = new bool[verticesCount()]();
        Node<Vertex<T>>* temp = vertices.head;
        while (temp != nullptr && temp->data.id != startId) {
            temp = temp->next;
        }
        if (temp != nullptr) {
            DFSUtil(temp->data, visited);
        }
        delete[] visited;
    }

    int verticesCount() {
        int count = 0;
        Node<Vertex<T>>* temp = vertices.head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    Graph<int> g;

    Vertex<int> v1(1);
    Vertex<int> v2(2);
    Vertex<int> v3(3);
    Vertex<int> v4(4);
    Vertex<int> v5(5);

    v1.adjList.pushBack(2);
    v1.adjList.pushBack(3);

    v2.adjList.pushBack(1);
    v2.adjList.pushBack(4);

    v3.adjList.pushBack(1);
    v3.adjList.pushBack(5);

    v4.adjList.pushBack(2);

    v5.adjList.pushBack(3);

    g.insert(v1);
    g.insert(v2);
    g.insert(v3);
    g.insert(v4);
    g.insert(v5);

    std::cout << "Graph:" << std::endl;
    g.display();
    std::cout << std::endl;

    std::cout << "BFS Traversal from vertex 1: ";
    g.BFS(1);
    std::cout << std::endl;

    std::cout << "DFS Traversal from vertex 1: ";
    g.DFS(1);
    std::cout << std::endl;

    std::cout << "BFS Traversal from vertex 3: ";
    g.BFS(3);
    std::cout << std::endl;

    std::cout << "DFS Traversal from vertex 3: ";
    g.DFS(3);
    std::cout << std::endl;

    return 0;
}
