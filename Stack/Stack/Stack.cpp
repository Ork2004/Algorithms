#include <iostream>
#include <vector>

using namespace std;

class Stack {
private:
    int size;
    int *arr;
    int top;
public:
    Stack(int maxSize) {
        top = -1;
        size = maxSize;
        arr = new int[maxSize];
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int x) {
        if (top == size - 1) {
            throw out_of_range("overflow");
        }
        else
        {
            arr[++top] = x;
        }
    }

    int pop() {
        if (top == -1) {
            throw out_of_range("underflow");
        }
        else
        {
            return arr[top--];
        }
    }

    void toString() {
        cout << "[";

        for (size_t i = 0; i <= top; ++i) {
            cout << arr[i];

            if (i != top) {
                cout << ", ";
            }
        }

        cout << "]";
    }
};

int main()
{
    Stack stack(10);

    stack.push(1);
    stack.push(2);
    stack.push(3);

    cout << "Popping: " << stack.pop() << std::endl;
    stack.toString();
}