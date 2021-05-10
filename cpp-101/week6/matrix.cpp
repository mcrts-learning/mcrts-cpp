#include <iostream>
#include <vector>
using namespace std;

int somme_consecutifs_max(vector<int> u);
vector<size_t> lignes_max(vector<vector<int>> mat);
vector<vector<int>> tranches_max(vector<vector<int>> mat);

int somme_consecutifs_max(vector<int> u){
    int best_sum(0);
    int buffer_sum(0);
    for (auto x : u) {
        if (x != 0) {
            buffer_sum += x;
        } else {
            best_sum = max(buffer_sum, best_sum);
            buffer_sum = 0;
        }
    }
    best_sum = max(buffer_sum, best_sum);
    return best_sum;
}

vector<size_t> lignes_max(vector<vector<int>> mat) {
    vector<size_t> result;
    int result_sum(0);

    for (size_t i(0); i < mat.size(); i++) {
        int row_sum(somme_consecutifs_max(mat[i]));
        if (row_sum > result_sum) {
            result = vector<size_t>({i});
            result_sum = row_sum;
        } else if (row_sum == result_sum) {
            result.push_back(i);
        }
    }
    return result;
}

vector<vector<int>> tranches_max(vector<vector<int>> mat) {
    vector<vector<int>> result;
    for (auto i : lignes_max(mat)) {
        result.push_back(mat[i]);
    }
    return result;
}

int main() {
    vector<int> u1({0, 2, 2, 0});
    vector<int> u2({2, 3, 0, 0, 4});
    vector<int> u3({4, 0, 2, 3});
    vector<int> u4({0, 0, 0, 0, 0});
    cout << boolalpha << "somme_consecutifs_max u1 should equal 4 : " << (4 == somme_consecutifs_max(u1)) << endl
                      << "somme_consecutifs_max u2 should equal 5 : " << (5 == somme_consecutifs_max(u2)) << endl
                      << "somme_consecutifs_max u3 should equal 5 : " << (5 == somme_consecutifs_max(u3)) << endl
                      << "somme_consecutifs_max u4 should equal 0 : " << (0 == somme_consecutifs_max(u4)) << endl;
    vector<vector<int>> mat1({
        {2, 1, 0, 2},
        {0, 1, 0, 3},
        {1, 3, 0, 0},
        {0, 2, 2, 0},
    });
    cout << boolalpha << "lignes_max mat1 should equal {2, 3} : " << (lignes_max(mat1) == vector<size_t>({2, 3})) << endl;
    
    vector<vector<int>> mat2({
        {2, 1, 0, 2, 0, 3, 2},
        {0, 1, 0, 7, 0},
        {1, 0, 1, 3, 2, 0, 3, 0, 4},
        {5, 0, 5},
        {1, 1, 1, 1, 1, 1, 1},
    });
    vector<vector<int>> res2({
        {0, 1, 0, 7, 0},
        {1, 1, 1, 1, 1, 1, 1},
    });
    cout << boolalpha << "tranches_max mat2 should equal res2 : " << (tranches_max(mat2) == res2) << endl;
    cout << boolalpha << "tranches_max of empty should return empty : " << (tranches_max(vector<vector<int>>()) == vector<vector<int>>()) << endl;
    vector<vector<int>> mat3({
        {},
        {0, 1, 0, 7, 0},
        {1, 0, 1, 3, 2, 0, 3, 0, 4},
        {5, 0, 5},
        {1, 1, 1, 1, 1, 1, 1},
    });
    vector<vector<int>> res3({
        {0, 1, 0, 7, 0},
        {1, 1, 1, 1, 1, 1, 1},
    });
    cout << boolalpha << "tranches_max mat3 should return res3 : " << (tranches_max(mat3) == res3) << endl;

    vector<vector<int>> mat4({
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
    });
    cout << boolalpha << "tranches_max all 1 should return same matrix : " << (tranches_max(mat4) == mat4) << endl;

    vector<vector<int>> mat5({
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    });
    cout << boolalpha << "tranches_max all 0 should return same matrix : " << (tranches_max(mat5) == mat5) << endl;


    vector<vector<int>> mat6({
        {2, 1, 2, 3, 2},
        {1, 7},
        {1, 1, 3, 2, 3, 4},
        {5, 5},
        {1, 1, 1, 1, 1, 1, 1},
    });
    vector<vector<int>> res6({
        {1, 1, 3, 2, 3, 4},
    });
    cout << boolalpha << "tranches_max no 0 (mat6) should return res6 : " << (tranches_max(mat6) == res6) << endl;
    
    return 0;
}