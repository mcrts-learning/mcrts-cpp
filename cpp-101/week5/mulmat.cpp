#include <iostream>
#include <vector>
using namespace std;

void affiche_matrice(const vector<vector<double>>& M) {
    for (auto row : M) {
        cout << " | ";
        for (auto x : row) {
            cout << x << " | ";
        }
        cout << endl;
    }
}

void affiche_vector(const vector<double>& u) {
    cout << "[ ";
    for (auto x : u) {
        cout << x << " ";
    }
    cout << "]" << endl;
}

vector<vector<double>> transpose(const vector<vector<double>>& Mat) {
    size_t row_size(Mat.size());
    size_t col_size(Mat[0].size());
    vector<vector<double>> newMat(
        col_size,
        vector<double>(row_size)
    );

    for (size_t i(0); i < row_size; i++) {
        for (size_t j(0); j < col_size; j++) {
            newMat[j][i] = Mat[i][j];
        }
    }
    return newMat;
}

double scalaire(vector<double> u, vector<double> v){
    double result(0);
    for (size_t i(0); i < u.size(); i++) {
        result += u[i] * v[i];
    }
    return result;
}

vector<vector<double>> multiplication(const vector<vector<double>>& Mat1,
                                      const vector<vector<double>>& Mat2) {
    size_t row_size(Mat1.size());
    size_t col_size(Mat2[0].size());
    vector<vector<double>> mat(
        row_size,
        vector<double>(col_size)
    );
    vector<vector<double>> Mat2t(transpose(Mat2));
    for (size_t i(0); i < row_size; i++) {
        vector<double> row(Mat1[i]);
        for (size_t j(0); j < col_size; j++) {
            vector<double> col(Mat2t[j]);
            mat[i][j] = scalaire(row, col);
        }
    }
    return mat;
}

int main() {
    vector<vector<double>> m1;
    vector<vector<double>> m2;
    m1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    m2 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 0, 1, 2}
    };

    affiche_matrice(m1);
    cout << endl;
    affiche_matrice(m2);
    cout << endl;
    affiche_matrice(multiplication(m1, m2));
    return 0;
}