#include <iostream>
#include <random>

using namespace std;

vector<vector<int>> generateRandomMatrix(int n) {
    srand(static_cast<unsigned int>(time(0)));
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

int main(){
    int n = 3;
    vector<vector<int>> A = generateRandomMatrix(n);
    printMatrix(A);
    return 0;
}