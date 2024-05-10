#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& arr, int beg, int end) {
    int pivot = arr[beg];
    int i = end + 1;

    for (int j = end; j > beg; j--) {
        if (arr[j] <= pivot) {
            i--;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i - 1], arr[beg]);
    return i - 1;
}

int randomPartition(vector<int>& arr, int beg, int end) {
    srand((unsigned)time(NULL));
    int i = (rand() % (end - beg)) + beg;
    swap(arr[end], arr[i]);
    return partition(arr, beg, end);
}

void quicksort(vector<int>& arr, int beg, int end) {
    if (beg < end) {
        int pi = randomPartition(arr, beg, end);

        quicksort(arr, beg, pi - 1);
        quicksort(arr, pi + 1, end);
    }
}

void toString(vector<int> arr) {
    cout << "[";

    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i];

        if (i != arr.size() - 1) {
            cout << ", ";
        }
    }

    cout << "]";
}

int main() {
    vector<int> arr = { 10, 7, 8, 9, 1, 5 };
    int n = arr.size();
    quicksort(arr, 0, n - 1);
    toString(arr);

    return 0;
}
