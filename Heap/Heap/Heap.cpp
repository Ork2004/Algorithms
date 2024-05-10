#include <iostream>
#include <vector>

using namespace std;

class Heaps
{
private:
	vector<int> arr;
public:
	Heaps(vector<int> arr, int length) {
		this->arr = arr;
		int n = arr.size();
		for (int i = arr.size() / 2 - 1; i >= 0; i--) {
			heapify(i, n);
		}
	}

	int left_child(int i) {
		int left = 2 * i + 1;
		return left;
	}

	int right_child(int i) {
		int right = 2 * i + 2;
		return right;
	}

	void heapify(int i, int n) {
		int largest = i;
		int leftChild = left_child(i);
		int rightChild = right_child(i);

		if (leftChild < n && arr[leftChild] > arr[largest])
			largest = leftChild;

		if (rightChild < n && arr[rightChild] > arr[largest])
			largest = rightChild;

		if (largest != i) {
			swap(arr[i], arr[largest]);
			heapify(largest, n);
		}
	}

	void heapSort() {
		int n = arr.size();

		for (int i = n - 1; i > 0; i--) {
			swap(arr[0], arr[i]);
			heapify(0 , i);
		}
	}

	void toString() {
		cout << "[";

		for (size_t i = 0; i < arr.size(); ++i) {
			cout << arr[i];

			if (i != arr.size() - 1) {
				cout << ", ";
			}
		}

		cout << "]";
	}
};

int main()
{
	vector<int> arr = { 5 , 9 , 6 , 7 , 2 , 4 , 9 , 2 , 1 , 8 };
	int length = arr.size();


	Heaps h1(arr, length);
	h1.heapSort();
	h1.toString();
}