#include <vector>
#include <memory>
#include <iostream>
#include <cassert>
#include "../utils/utils.hpp"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::endl;
using std::cout;
using matrix = std::vector<vector<int>>;
using matrix_ptr = shared_ptr<matrix>;

void init_mat(matrix &mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        vector<int> row;
        for (int j = 0; j < n; j++)
            row.push_back(randint(-9, 9));
        mat.push_back(row);
    }
}

matrix_ptr add_mat(const matrix& m1, 
                   const int r1,
                   const int c1,
                   const matrix& m2,
                   const int r2,
                   const int c2,
                   const int n)
{
    assert(m1.size() == m1[0].size() && "mat1 should be a nxn matrix");
    assert(m2.size() == m2[0].size() && "mat2 should be a nxn matrix");
    assert(m1.size() == m2.size() && "mat1 and mat2 should be same size");

    auto res = make_shared<matrix>(n, vector<int>(n));

    for(int r = 0; r < n; r++)
        for(int c = 0; c < n; c++)
            (*res)[r][c] = m1[r1 + r][c1 + c] + m2[r2 + r][c2 + c];

    return res;
}

void assign_mat(const matrix &src, 
                matrix &des, 
                const int row, 
                const int col)
{
    int n = src.size();
    for(int r = 0; r < n; r++)
        for(int c = 0; c < n; c++)
            des[row + r][col + c] = src[r][c];
}
matrix_ptr strassen(const matrix &ma, 
                    const int r1, 
                    const int c1, 
                    const matrix &mb, 
                    const int r2, 
                    const int c2, 
                    const int n)
{
    assert(ma.size() == ma[0].size() && "mat1 should be a nxn matrix");
    assert(mb.size() == mb[0].size() && "mat2 should be a nxn matrix");
    assert(ma.size() == mb.size() && "mat1 and mat2 should be same size");

    if(n == 2)
    {
        //ma
        int a00 = ma[r1][c1];
        int a01 = ma[r1][c1 + 1];
        int a10 = ma[r1 + 1][c1];
        int a11 = ma[r1 + 1][c1 + 1];

        //mb
        int b00 = mb[r2][c2];
        int b01 = mb[r2][c2 + 1];
        int b10 = mb[r2 + 1][c2];
        int b11 = mb[r2 + 1][c2 + 1];

        int m1 = (a00 + a11) * (b00 + b11);
        int m2 = (a10 + a11) * b00;
        int m3 = a00 * (b01 - b11);
        int m4 = a11 * (b10 - b00);
        int m5 = (a00 + a01) * b11;
        int m6 = (a10 - a00) * (b00 + b01);
        int m7 = (a01 - a11) * (b10 + b11);

        //mc
        matrix_ptr mc = make_shared<matrix>(2, vector<int>(2));
        (*mc)[0][0] = m1 + m4 - m5 + m7;
        (*mc)[0][1] = m3 + m5;
        (*mc)[1][0] = m2 + m4;
        (*mc)[1][1] = m1 + m3 - m2 + m6;

        return mc;
    }

    matrix_ptr res = make_shared<matrix>(n, vector<int>(n));

    matrix_ptr M1 = strassen(
        *add_mat(ma, r1, c1, ma, r1 + n / 2, c1 + n / 2, n / 2),
        *add_mat(mb, r2, c2, ));


    return res;
}

void print_mat(const matrix &m)
{
    cout << "=========================================" << endl;
    for(auto row : (m))
    {
        for(auto col : row)
            cout << col << "\t";
        cout << endl;
    }
}

int main()
{
    matrix m1;    
    matrix m2;
    init_mat(m1, 4);
    init_mat(m2, 4);
    //matrix_ptr res = strassen(m1, m2, 0, 0, 2);
    matrix_ptr res = add_mat(m1, 2, 2, m2, 2, 2, 2);

    print_mat(m1);
    print_mat(m2);
    print_mat(*res);

}