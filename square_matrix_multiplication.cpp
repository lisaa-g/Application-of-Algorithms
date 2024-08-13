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
            matrix[i][j] = rand() % 100; //random values between 0 and 99
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
vector<vector<int>> squareMatrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B){
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

//addition between matrix A and B
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

//subtraction between matrix A and B
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

//recursive square matrix multiplication between matrix A and B
vector<vector<int>> squareMatrixMultiplyRecursive(const vector<vector<int>>& A, const vector<vector<int>>& B) {
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

//pads matrix with zeroes to make it a matrix with size of power of 2
vector<vector<int>> padMatrix(const vector<vector<int>>& A, int newSize) {
    int oldSize = A.size();
    vector<vector<int>> padded(newSize, vector<int>(newSize, 0));
    for (int i = 0; i < oldSize; ++i) {
        for (int j = 0; j < oldSize; ++j) {
            padded[i][j] = A[i][j];
        }
    }
    return padded;
}

//unpads matrix so it is its original size
vector<vector<int>> unpadMatrix(const vector<vector<int>>& A, int originalSize) {
    vector<vector<int>> unpadded(originalSize, vector<int>(originalSize));
    for (int i = 0; i < originalSize; ++i) {
        for (int j = 0; j < originalSize; ++j) {
            unpadded[i][j] = A[i][j];
        }
    }
    return unpadded;
} 

//strassens method of square matrix multiplication between matrix A and B
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize, 0));
    vector<vector<int>> A12(newSize, vector<int>(newSize, 0));
    vector<vector<int>> A21(newSize, vector<int>(newSize, 0));
    vector<vector<int>> A22(newSize, vector<int>(newSize, 0));
    vector<vector<int>> B11(newSize, vector<int>(newSize, 0));
    vector<vector<int>> B12(newSize, vector<int>(newSize, 0));
    vector<vector<int>> B21(newSize, vector<int>(newSize, 0));
    vector<vector<int>> B22(newSize, vector<int>(newSize, 0));

    //dividing the matrices into quadrants
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

    //calculating the seven products, using the Strassen algorithm
    vector<vector<int>> P1 = strassen(add(A11, A22), add(B11, B22));
    vector<vector<int>> P2 = strassen(add(A21, A22), B11);
    vector<vector<int>> P3 = strassen(A11, subtract(B12, B22));
    vector<vector<int>> P4 = strassen(A22, subtract(B21, B11));
    vector<vector<int>> P5 = strassen(add(A11, A12), B22);
    vector<vector<int>> P6 = strassen(subtract(A21, A11), add(B11, B12));
    vector<vector<int>> P7 = strassen(subtract(A12, A22), add(B21, B22));

    //calculating C quadrants
    vector<vector<int>> C11 = add(subtract(add(P1, P4), P5), P7); //C11 = M1 + M4 - M5 + M7
    vector<vector<int>> C12 = add(P3, P5); //C12 = M3 + M5
    vector<vector<int>> C21 = add(P2, P4); //C21 = M2 + M4
    vector<vector<int>> C22 = add(subtract(add(P1, P3), P2), P6); //C22 = M1 + M3 - M2 + M6

    //combining the results into a single matrix
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
}

int main(){
    vector<int> dimensions = {12, 45, 69, 101, 154, 203, 317, 420, 487, 556, 678, 721, 889, 912, 1000, 1011, 1176, 1298, 1425, 1553, 1682, 1799, 1818, 1907, 2045};
    int numTests = 3; 

    ofstream file("results.csv");
    file << "Matrix Dimension, Normal SMM, Recursive SMM, Strassen SMM" << endl;

    for (int n : dimensions) {
        int newSize = pow(2, ceil(log2(n)));

        double SMMTime = 0.0;
        double recursiveSMMTime = 0.0;
        double strassenTime = 0.0;

        for (int i = 0; i < numTests; ++i) {
            vector<vector<int>> A = generateRandomMatrix(n);
            vector<vector<int>> B = generateRandomMatrix(n);

            auto start_time = high_resolution_clock::now();
            vector<vector<int>> C = squareMatrixMultiply(A, B);
            auto end_time = high_resolution_clock::now();
            double duration = duration_cast<microseconds>(end_time - start_time).count() / 1000000.0;
            SMMTime += duration;

            vector<vector<int>> paddedA = (newSize == n) ? A : padMatrix(A, newSize);
            vector<vector<int>> paddedB = (newSize == n) ? B : padMatrix(B, newSize);

            start_time = high_resolution_clock::now();
            vector<vector<int>> D = squareMatrixMultiplyRecursive(paddedA, paddedB);
            end_time = high_resolution_clock::now();
            duration = duration_cast<microseconds>(end_time - start_time).count() / 1000000.0;
            recursiveSMMTime += duration;

            start_time = high_resolution_clock::now();
            vector<vector<int>> E = strassen(paddedA, paddedB);
            end_time = high_resolution_clock::now();
            duration = duration_cast<microseconds>(end_time - start_time).count() / 1000000.0;
            strassenTime += duration;

        }

        double averageSMMTime = SMMTime / numTests;
        double averageRecursiveSMMTime = recursiveSMMTime / numTests;
        double averageStrassenTime = strassenTime / numTests;

        file << n << ", " << averageSMMTime << ", " << averageRecursiveSMMTime << ", " << averageStrassenTime << endl;
    }

    file.close();
    return 0;
}