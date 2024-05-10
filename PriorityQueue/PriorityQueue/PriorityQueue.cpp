#include <iostream>
#include <vector>

using namespace std;

class Heaps
{
private:
	vector<int> arr;
public:
	Heaps() {

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

	void insert(int key) {
		arr.push_back(INT_MIN);
		increaseKey(arr.size() - 1, key);
	}

	int maximum() {
		if (!arr.empty())
			return arr[0];
		else {
			std::cerr << "Error: Priority queue is empty." << std::endl;
			return INT_MIN;
		}
	}

	int extractMax() {
		if (arr.empty()) {
			std::cerr << "Error: Priority queue is empty." << std::endl;
			return INT_MIN;
		}

		int max = arr[0];
		arr[0] = arr.back();
		arr.pop_back();
		heapify(0 , arr.size());
		return max;
	}

	void increaseKey(int i, int key) {
		if (key < arr[i]) {
			std::cerr << "Error: New key is smaller than the current key." << std::endl;
			return;
		}

		arr[i] = key;
		while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
			swap(arr[i], arr[(i - 1) / 2]);
			i = (i - 1) / 2;
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

int main() {
	Heaps h1;

	h1.insert(4);
	h1.insert(10);
	h1.insert(2);
	h1.insert(7);

	cout << "Maximum element: " << h1.maximum() << endl;

	cout << "Extracted max element: " << h1.extractMax() << endl;

	cout << "New maximum element: " << h1.maximum() << endl;

	h1.increaseKey(2, 8);

	cout << "Maximum element after increasing key: " << h1.maximum() << endl;

	return 0;
}
