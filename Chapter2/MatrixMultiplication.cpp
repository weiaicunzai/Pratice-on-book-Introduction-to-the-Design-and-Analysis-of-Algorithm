#include <iostream>
#include <vector>
#include <cassert>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::vector;
using matrix = vector<vector<int>>;

void init_mat(matrix &mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        vector<int> row;
        for (int j = 0; j < n; j++)
            row.push_back(randint(-300, 300));
        mat.push_back(row);
    }
}

/**
 * @brief Multiplies two square matrices of order n by the definition-based algorithm
 * @param mat1 a nxn matrix
 * @param mat2 a nxn matrix
 * @output a matrix pointer points to a matrix contains mat multiplication result
 */
const matrix *mat_mul(const matrix &mat1, const matrix &mat2)
{
    assert(mat1.size() == mat1[0].size() && "mat should be a nxn matrix");
    assert(mat2.size() == mat2[0].size() && "mat should be a nxn matrix");
    assert(mat1.size() == mat2.size() && "mat1 and mat2 should be same size");
    matrix *temp = new matrix(mat1.size(), vector<int>(mat1.size(), 0));

    for (int row = 0; row < mat1.size(); row++)
        for (int col = 0; col < mat1.size(); col++)
            for (int k = 0; k < mat1.size(); k++)
                (*temp)[row][col] += (mat1[row][k] * mat2[k][col]);

    return temp;
}

void print_mat(const matrix &mat)
{
    cout << "---------" << endl;
    cout << "mat size: " << endl;
    cout << "row: " << mat.size() << endl;
    cout << "col: " << mat[0].size() << endl;
    cout << "---------" << endl;
    for (auto row : mat)
    {
        for (auto col : row)
            cout << col << "\t";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int mat_size = randint(1, 300);
    matrix mat1, mat2;

    init_mat(mat1, mat_size);
    init_mat(mat2, mat_size);

    const matrix *res = mat_mul(mat1, mat2);

    // print_mat(mat1);
    // print_mat(mat2);
    // print_mat(*res);
}