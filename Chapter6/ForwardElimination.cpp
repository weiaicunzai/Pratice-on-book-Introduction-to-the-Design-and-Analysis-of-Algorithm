#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <memory>
#include <iomanip>
#include "../utils/utils.hpp"

using std::abs;
using std::cout;
using std::endl;
using std::left;
using std::make_shared;
using std::setw;
using std::shared_ptr;
using std::swap;
using std::vector;
using matrix = vector<vector<double>>;
using column = vector<double>;
using matrix_ptr = shared_ptr<matrix>;
using column_ptr = shared_ptr<column>;

/**
 * @brief Applies Gaussian elimination to matrix A(m row x n col) of a 
 *        system's coefficients augmented with vector b of the system's 
 *        right-hand side values
 * @param A matrix A
 * @param column-vector b
 * @output an equivalent upper-triangular matrix in place of A with the
 *         corresponding right-hand side values in the (n + 1)st column
 */
void forward_elimination(matrix_ptr A, column_ptr b)
{
    assert(A->size() > 0 && "A's row number should be larger than 1");
    assert(A->size() == b->size() && "A and b should have the same row number");
    assert(A->size() == A->at(0).size() && "A should be a nxn matrix");
    for (int i = 0; i < A->size(); i++)
        A->at(i).push_back(b->at(i));

    int n = A->size();
    for (int row_idx_v = 0; row_idx_v < n - 1; row_idx_v++)
    {
        int pivot_row = row_idx_v;
        int pivot_col = pivot_row; //pivots are on the diagonal

        //avoid round-off error
        for (int row_idx_u = row_idx_v + 1; row_idx_u < n; row_idx_u++)
            if (abs((*A)[row_idx_u][pivot_col]) > abs((*A)[row_idx_v][pivot_col]))
                pivot_row = row_idx_u;

        swap(A->at(pivot_row), A->at(row_idx_v));
        pivot_row = row_idx_v;

        for (int row_idx_u = row_idx_v + 1; row_idx_u < n; row_idx_u++)
        {
            double temp = (*A)[row_idx_u][pivot_col] / (*A)[pivot_row][pivot_col];
            for (int col = pivot_col; col < n + 1; col++)
                (*A)[row_idx_u][col] = (*A)[row_idx_u][col] - (*A)[pivot_row][col] * temp;
        }
    }

    for (int i = 0; i < A->size(); i++)
    {
        (*b)[i] = (*A)[i].back();
        (*A)[i].pop_back();
    }
}

void init_mat(matrix_ptr mat, double n, double min, int max)
{
    for (int i = 0; i < n; i++)
    {
        vector<double> row;
        for (int j = 0; j < n; j++)
            row.push_back(randouble(min, max));
        mat->push_back(row);
    }
}

int main()
{
    int n = randint(5, 10);

    matrix_ptr A = make_shared<matrix>();
    init_mat(A, n, -10, 10);

    column_ptr b = make_shared<column>();
    for (int i = 0; i < n; i++)
        b->push_back(randouble(-10, 10));

    forward_elimination(A, b);

    //print A
    cout << "A: " << endl;
    for (auto row : *A)
    {
        for (auto x : row)
            cout << left << setw(13) << x;
        cout << endl;
    }

    //print b
    cout << endl;
    cout << "b:" << endl;
    for (auto x : *b)
        cout << x << endl;
}