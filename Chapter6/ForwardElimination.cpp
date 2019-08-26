#include <vector>
#include <iostream>
#include <cassert>
#include <memory>

using std::cout;
using std::endl;
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

    for(int row = 0; row < A->size() - 1; row++)
    {
        for(int r = row + 1; r < A->size(); r++)
    }

}
int main()
{
}