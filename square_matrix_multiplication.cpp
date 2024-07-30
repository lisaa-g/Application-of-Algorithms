#include <iostream>
#include <random>

using namespace std;

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
    int n = 3;
    vector<vector<int>> A = generateRandomMatrix(n);
    printMatrix(A);
    vector<vector<int>> B = generateRandomMatrix(n);
    printMatrix(B);
    squareMatrixMultiply(A, B);
    printMatrix(squareMatrixMultiply(A,B));
    return 0;
}