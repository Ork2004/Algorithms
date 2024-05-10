#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> squareMatrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

vector<vector<int>> squareMatrixMultiplyRecursive(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    if (n == 1)  C[0][0] = A[0][0] * B[0][0];
    else
    {
        vector<vector<int>> A11(n / 2, vector<int>(n / 2));
        vector<vector<int>> A12(n / 2, vector<int>(n / 2));
        vector<vector<int>> A21(n / 2, vector<int>(n / 2));
        vector<vector<int>> A22(n / 2, vector<int>(n / 2));
        vector<vector<int>> B11(n / 2, vector<int>(n / 2));
        vector<vector<int>> B12(n / 2, vector<int>(n / 2));
        vector<vector<int>> B21(n / 2, vector<int>(n / 2));
        vector<vector<int>> B22(n / 2, vector<int>(n / 2));

        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n / 2; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n / 2];
                A21[i][j] = A[i + n / 2][j];
                A22[i][j] = A[i + n / 2][j + n / 2];
            }
        }

        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n / 2; ++j) {
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n / 2];
                B21[i][j] = B[i + n / 2][j];
                B22[i][j] = B[i + n / 2][j + n / 2];
            }
        }

        vector<vector<int>> C11 = addMatrices(squareMatrixMultiplyRecursive(A11, B11), squareMatrixMultiplyRecursive(A12, B21));
        vector<vector<int>> C12 = addMatrices(squareMatrixMultiplyRecursive(A11, B12), squareMatrixMultiplyRecursive(A12, B22));
        vector<vector<int>> C21 = addMatrices(squareMatrixMultiplyRecursive(A21, B11), squareMatrixMultiplyRecursive(A22, B21));
        vector<vector<int>> C22 = addMatrices(squareMatrixMultiplyRecursive(A21, B12), squareMatrixMultiplyRecursive(A22, B22));

        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n / 2; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + n / 2] = C12[i][j];
                C[i + n / 2][j] = C21[i][j];
                C[i + n / 2][j + n / 2] = C22[i][j];
            }
        }
    }
    return C;
}

int main()
{
    vector<vector<int>> A = { {1, 2}, {3, 4} };
    vector<vector<int>> B = { {5, 6}, {7, 8} };

    vector<vector<int>> C1 = squareMatrixMultiply(A, B);
    vector<vector<int>> C2 = squareMatrixMultiplyRecursive(A, B);

    cout << "Resultant matrix:" << endl;
    cout << "whithout Recursive:" << endl;
    for (const auto& row : C1) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }

    cout << "whith Recursive:" << endl;
    for (const auto& row : C2) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}
