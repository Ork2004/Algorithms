#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int max(int a, int b, int c) {
    return max(max(a, b), c);
}

vector<int> maxSumarrayCrossing(vector<int> arr, int beg, int mid, int end) {
    int left_sum = INT_MIN;
    int max_left = mid, max_right = mid + 1;
    int sum = 0;
    for (int i = mid; i >= beg; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    sum = 0;
    int right_sum = INT_MIN;
    for (int i = mid+1; i <= end; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }

    vector<int> left_arr{ max_left, mid, left_sum };
    vector<int> right_arr{ mid + 1,max_right, right_sum };
    vector<int> cross_arr{ max_left, max_right, left_sum + right_sum };
    if (left_arr[2] >= right_arr[2] && left_arr[2] >= cross_arr[2]) return left_arr;
    else if (right_arr[2] >= left_arr[2] && right_arr[2] >= cross_arr[2]) return right_arr;
    else return cross_arr;
}

vector<int> maxSubarray(vector<int> arr, int beg, int end) {
    if (end == beg) {
        vector<int> array{ beg,end,arr[beg] };
        return array;
    }
    else
    {
        int mid = (beg + end) / 2;

        vector<int> left_arr = maxSubarray(arr, beg, mid);
        vector<int> right_arr = maxSubarray(arr, mid + 1, end);
        vector<int> cross_arr = maxSumarrayCrossing(arr, beg, mid, end);
        if (left_arr[2] >= right_arr[2] && left_arr[2] >= cross_arr[2]) return left_arr;
        else if (right_arr[2] >= left_arr[2] && right_arr[2] >= cross_arr[2]) return right_arr;
        else return cross_arr;
    }
}

int main()
{
    vector<int> arr;
    int num;

    while (true) {
        std::cin >> num;

        if (num == -1) {
            break;
        }

        arr.push_back(num);
    }

    vector<int> array = maxSubarray(arr, 0, arr.size() - 1);

    for (int i = 0; i < 3; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << endl;
    return 0;
}
