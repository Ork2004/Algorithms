#include <iostream>
#include <vector>

using namespace std;

//1
//Upon examining the pseudocode for insertion sort while considering the definition of inversions, we notice that the inner while loop runs more frequently when there are more inversions in the array.
//Therefore, as the number of inversions in an array increases, the insertion sort algorithm will take longer to sort the array.

//2
int Merge(vector<int>& A, int beg, int mid, int end) {
    int n1 = mid - beg + 1;
    int n2 = end - mid;
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    for (int i = 0; i < n1; i++)
        L[i] = A[beg + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + j + 1];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    int inversions = 0;

    for (int k = beg; k <= end; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
            inversions += (n1 - i);
        }
    }

    return inversions;
}

int MergeSort(vector<int>& A, int beg, int end) {
    if (beg >= end) return 0;

    int mid = (beg + end) / 2;
    int left = MergeSort(A, beg, mid);
    int right = MergeSort(A, mid + 1, end);
    int inversions = left + right + Merge(A, beg, mid, end);

    return inversions;
}

//4

//The loop condition while p < r in quicksort should be p <= r for correctness.
//Furthermore, recursive calls should sort both leftand right subarrays, not just the left, to ensure proper sorting.
//But everything works here

int partition(int A[], int p, int r) {
    int pivot = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void TailRecursiveQuicksort(int A[], int p, int r) {
    while (p < r) {
        int q = partition(A, p, r);
        TailRecursiveQuicksort(A, p, q - 1);
        p = q + 1;
    }
}

int main()
{
    //2
    vector<int> arr1 = { 1, 20, 6, 4, 5 };
    int inversions = MergeSort(arr1, 0, arr1.size() - 1);
    cout << "Number of inversions: " << inversions << endl;


    //4
    int arr2[] = { 9, 2, 5, 1, 7, 4, 8, 3, 6 };
    int n = sizeof(arr2) / sizeof(arr2[0]);

    std::cout << "Array before sorting: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    TailRecursiveQuicksort(arr2, 0, n - 1);

    std::cout << "Array after sorting: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

}
