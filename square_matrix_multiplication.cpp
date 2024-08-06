#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

vector<vector<int>> generateRandomMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    //fill the matrix with random values
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10; //random values between 0 and 99
        }
    }

    return matrix;
}

//print matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//square matrix multiplication between matrix A and B
vector<vector<int>> squareMatrixMultiply(vector<vector<int>> A, vector<vector<int>> B){
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            C[i][j] = 0;
            for (int k=0; k<n; k++){
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vector<vector<int>> add(const vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<int>> subtract(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

vector<vector<int>> squareMatrixMultiplyRecursive(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        vector<vector<int>> A11(newSize, vector<int>(newSize, 0));
        vector<vector<int>> A12(newSize, vector<int>(newSize, 0));
        vector<vector<int>> A21(newSize, vector<int>(newSize, 0));
        vector<vector<int>> A22(newSize, vector<int>(newSize, 0));
        vector<vector<int>> B11(newSize, vector<int>(newSize, 0));
        vector<vector<int>> B12(newSize, vector<int>(newSize, 0));
        vector<vector<int>> B21(newSize, vector<int>(newSize, 0));
        vector<vector<int>> B22(newSize, vector<int>(newSize, 0));

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        vector<vector<int>> C11 = add(squareMatrixMultiplyRecursive(A11, B11), squareMatrixMultiplyRecursive(A12, B21));
        vector<vector<int>> C12 = add(squareMatrixMultiplyRecursive(A11, B12), squareMatrixMultiplyRecursive(A12, B22));
        vector<vector<int>> C21 = add(squareMatrixMultiplyRecursive(A21, B11), squareMatrixMultiplyRecursive(A22, B21));
        vector<vector<int>> C22 = add(squareMatrixMultiplyRecursive(A21, B12), squareMatrixMultiplyRecursive(A22, B22));

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }
    return C;
}

vector<vector<int>> padMatrix(vector<vector<int>> A, int newSize) {
    int oldSize = A.size();
    vector<vector<int>> padded(newSize, vector<int>(newSize, 0));
    for (int i = 0; i < oldSize; ++i) {
        for (int j = 0; j < oldSize; ++j) {
            padded[i][j] = A[i][j];
        }
    }
    return padded;
}

vector<vector<int>> unpadMatrix(vector<vector<int>> A, int originalSize) {
    vector<vector<int>> unpadded(originalSize, vector<int>(originalSize));
    for (int i = 0; i < originalSize; ++i) {
        for (int j = 0; j < originalSize; ++j) {
            unpadded[i][j] = A[i][j];
        }
    }
    return unpadded;
} 

int main(){
    vector<int> dimensions = {10, 20, 30, 40, 50};  // Example dimensions
    int numTests = 1;  // Number of random matrices to average over

    ofstream file("results.csv");
    file << "Matrix Dimension, Algorithm, Average Runtime (microseconds)" << endl;

    int newSize = pow(2, ceil(log2(3)));

    // for (int n : dimensions) {
    //     long totalTime = 0.0;

    //     for (int i = 0; i < numTests; ++i) {
    //         vector<vector<int>> A = generateRandomMatrix(n);
    //         vector<vector<int>> B = generateRandomMatrix(n);

    //         auto start_time = high_resolution_clock::now();
    //         vector<vector<int>> C = squareMatrixMultiply(A, B);
    //         auto end_time = high_resolution_clock::now();

    //         auto duration = duration_cast<microseconds>(end_time - start_time).count();
    //         totalTime += duration;
    //     }

    //     double averageRuntime = totalTime / numTests;
    //     file << n << ", Square Matrix Multiply, " << averageRuntime << endl;
    // }

    vector<vector<int>> A = generateRandomMatrix(3);
    vector<vector<int>> B = generateRandomMatrix(3);
    vector<vector<int>> paddedA = (newSize == 3) ? A : padMatrix(A, newSize);
    vector<vector<int>> paddedB = (newSize == 3) ? B : padMatrix(B, newSize);
    vector<vector<int>> C = squareMatrixMultiply(A, B);
    vector<vector<int>> D = squareMatrixMultiplyRecursive(paddedA, paddedB);
    vector<vector<int>> Dunpadded = (newSize == 3) ? D : unpadMatrix(D, 3);
    printMatrix(A);
    printMatrix(B);
    printMatrix(C);
    printMatrix(D);
    printMatrix(Dunpadded);

    file.close();
    return 0;
}