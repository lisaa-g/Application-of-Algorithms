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

int main(){
    vector<int> dimensions = {10, 20, 30, 40, 50};  // Example dimensions
    int numTests = 5;  // Number of random matrices to average over

    ofstream file("results.csv");
    file << "Matrix Dimension, Algorithm, Average Runtime (microseconds)" << endl;
    for (int n : dimensions) {
        long totalTime = 0.0;

        for (int i = 0; i < numTests; ++i) {
            vector<vector<int>> A = generateRandomMatrix(n);
            vector<vector<int>> B = generateRandomMatrix(n);

            auto start_time = high_resolution_clock::now();
            vector<vector<int>> C = squareMatrixMultiply(A, B);
            auto end_time = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(end_time - start_time).count();
            totalTime += duration;
        }

        double averageRuntime = totalTime / numTests;
        file << n << ", Square Matrix Multiply, " << averageRuntime << endl;
    }

    file.close();
    return 0;
}