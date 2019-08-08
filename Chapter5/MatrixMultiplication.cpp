#include <vector>
#include <memory>
#include <iostream>
#include <cassert>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::make_shared;
using std::pow;
using std::shared_ptr;
using std::vector;
using matrix = std::vector<vector<int>>;
using matrix_ptr = shared_ptr<matrix>;

void init_mat(matrix_ptr mat, int n, int min, int max)
{
    for (int i = 0; i < n; i++)
    {
        vector<int> row;
        for (int j = 0; j < n; j++)
            row.push_back(randint(min, max));
        mat->push_back(row);
    }
}

/**
 * @brief add two matrixes, they need to be both nxn shape
 * @param m1 m2 matrix pointer
 * @param n matrix size
 * @output added matrix pointer
 */
matrix_ptr add_mat(const matrix_ptr m1, const matrix_ptr m2)
{
    assert(m1->size() == (*m1)[0].size() && "mat1 should be a nxn matrix");
    assert(m2->size() == (*m2)[0].size() && "mat2 should be a nxn matrix");
    assert(m1->size() == m2->size() && "mat1 and mat2 should be same size");

    int n = m1->size();
    auto res = make_shared<matrix>(n, vector<int>(n));

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            (*res)[r][c] = (*m1)[r][c] + (*m2)[r][c];

    return res;
}

/**
 * @brief subtract one matrixes from another, they need to be both in nxn shape
 * @param m1 m2 matrix pointer
 * @param n matrix size
 * @output added matrix pointer
 */
matrix_ptr subtract_mat(const matrix_ptr m1, const matrix_ptr m2)
{
    assert(m1->size() == (*m1)[0].size() && "mat1 should be a nxn matrix");
    assert(m2->size() == (*m2)[0].size() && "mat2 should be a nxn matrix");
    assert(m1->size() == m2->size() && "mat1 and mat2 should be same size");

    int n = m1->size();
    auto res = make_shared<matrix>(n, vector<int>(n));

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            (*res)[r][c] = (*m1)[r][c] - (*m2)[r][c];

    return res;
}

/**
 * @brief copy src matrix to des
 * @param src source matrix, shape need to be smaller than des
 * @param des matrix
 * @param top left row index of des matrix where src matrix's
 *        top left corner to be copied at
 * @param col same as row.
 * @output des matrix
 */
void copy_mat(const matrix_ptr src,
              matrix_ptr des,
              const int row,
              const int col)
{
    assert(src->size() <= des->size() && (*src)[0].size() <= (*des)[0].size());
    assert(row >= 0 && row <= des->size() - src->size());
    assert(col >= 0 && col <= (*des).size() - (*src).size());

    int n = src->size();
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            (*des)[row + r][col + c] = (*src)[r][c];
}

/**
 * @brief slice a matrix to a (nxn) size submatrix
 * @param m source matrix need to be sliced
 * @param row submatrix top left row index
 * @param col submatrix top left col index
 * @param n submatrix size
 * @output a smart pointer points to the submatrix
 */
matrix_ptr slice_mat(const matrix_ptr m, const int row, const int col, const int n)
{
    assert(row >= 0 && col >= 0);
    assert(row < m->size() && col < m->size());
    auto submatrix = make_shared<matrix>(n, vector<int>(n));
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            (*submatrix)[r][c] = (*m)[r + row][c + col];

    return submatrix;
}

/**
 * @biref perform strassen's matrix mulitplication
 * @param ma matrix need to multiply
 * @param r1 c1 submatrix's top left row and coloumn index
 * @param mb matrix need to multiply
 * @param r2 c2 submatrix's top left row and coloumn index
 * @param n matrix shape (nxn)
 * @output return  a smart pointer to nxn shape matrix
 */
matrix_ptr strassen(const matrix_ptr ma, const matrix_ptr mb)
{
    assert(ma->size() == (*ma)[0].size() && "mat1 should be a nxn matrix");
    assert(mb->size() == (*mb)[0].size() && "mat2 should be a nxn matrix");
    assert(ma->size() == mb->size() && "mat1 and mat2 should be same size");

    int n = ma->size();

    if (n == 2)
    {
        //ma
        int a00 = (*ma)[0][0];
        int a01 = (*ma)[0][1];
        int a10 = (*ma)[1][0];
        int a11 = (*ma)[1][1];

        //mb
        int b00 = (*mb)[0][0];
        int b01 = (*mb)[0][1];
        int b10 = (*mb)[1][0];
        int b11 = (*mb)[1][1];

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

    matrix_ptr a00 = slice_mat(ma, 0, 0, n / 2);
    matrix_ptr a01 = slice_mat(ma, 0, n / 2, n / 2);
    matrix_ptr a10 = slice_mat(ma, n / 2, 0, n / 2);
    matrix_ptr a11 = slice_mat(ma, n / 2, n / 2, n / 2);

    matrix_ptr b00 = slice_mat(mb, 0, 0, n / 2);
    matrix_ptr b01 = slice_mat(mb, 0, n / 2, n / 2);
    matrix_ptr b10 = slice_mat(mb, n / 2, 0, n / 2);
    matrix_ptr b11 = slice_mat(mb, n / 2, n / 2, n / 2);

    matrix_ptr m1 = strassen(add_mat(a00, a11), add_mat(b00, b11));
    matrix_ptr m2 = strassen(add_mat(a10, a11), b00);
    matrix_ptr m3 = strassen(a00, subtract_mat(b01, b11));
    matrix_ptr m4 = strassen(a11, subtract_mat(b10, b00));
    matrix_ptr m5 = strassen(add_mat(a00, a01), b11);
    matrix_ptr m6 = strassen(subtract_mat(a10, a00), add_mat(b00, b01));
    matrix_ptr m7 = strassen(subtract_mat(a01, a11), add_mat(b10, b11));

    matrix_ptr c00 = add_mat(m1, m4);
    c00 = subtract_mat(c00, m5);
    c00 = add_mat(c00, m7);

    matrix_ptr c01 = add_mat(m3, m5);

    matrix_ptr c10 = add_mat(m2, m4);

    matrix_ptr c11 = add_mat(m1, m3);
    c11 = subtract_mat(c11, m2);
    c11 = add_mat(c11, m6);

    //copy 4 sub matrix to res
    copy_mat(c00, res, 0, 0);
    copy_mat(c01, res, 0, n / 2);
    copy_mat(c10, res, n / 2, 0);
    copy_mat(c11, res, n / 2, n / 2);

    return res;
}

void print_mat(const matrix_ptr &m)
{
    cout << "=========================================" << endl;
    for (auto row : (*m))
    {
        for (auto col : row)
            cout << col << "\t";
        cout << endl;
    }
}

int main()
{
    matrix_ptr m1 = make_shared<matrix>();
    matrix_ptr m2 = make_shared<matrix>();

    //for simplicity reason, only test for 2^n x 2^n
    //shape matrix
    int n = randint(1, 5);
    init_mat(m1, pow(2, n), -9, 9);
    init_mat(m2, pow(2, n), -9, 9);

    matrix_ptr res = strassen(m1, m2);

    print_mat(m1);
    print_mat(m2);
    print_mat(res);
}