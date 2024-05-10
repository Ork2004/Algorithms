#include <iostream>

class Queue {
private:
    int* arr;
    int head;
    int tail;
    int length;

public:
    Queue(int size) {
        arr = new int[size];
        head = tail = 0;
        length = size;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int x) {
        arr[tail] = x;
        if (tail == length - 1) {
            tail = 0;
        }
        else {
            tail++;
        }
    }

    int dequeue() {
        int x = arr[head];
        if (head == length - 1 || head == tail - 1) {
            head = 0;
        }
        else {
            head++;
        }
        return x;
    }
};

int main() {
    Queue myQueue(6);

    myQueue.enqueue(1);
    myQueue.enqueue(2);
    myQueue.enqueue(3);

    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;
    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;
    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;
    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;

    myQueue.enqueue(4);
    myQueue.enqueue(5);

    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;
    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;
    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;
    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;
    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;
    std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;


    return 0;
}
