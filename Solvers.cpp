#include "Solvers.hpp"
#include "LinearSystem.hpp"
#include <cmath>
#include <iostream>

namespace coma {
Vector GaussSolver::solve() {
    forwardPath();
    Vector root(LS->getSize());
    backwardPath(root);
    return root;
}

void GaussSolver::forwardPath() {
    for (size_t iter = 0; iter < LS->getSize(); iter++) {
        chooseMaxCoeff(iter);
        nullifyCol(iter);
    }
}

void GaussSolver::chooseMaxCoeff(size_t iter) {
    Matrix &matrix = LS->matrix();
    numb_t max = matrix[iter][iter];
    size_t max_index = iter;
    for (size_t i = iter; i < LS->getSize(); i++) {
        if (fabs(max) < fabs(matrix[iter][i])) {
            max = matrix[iter][i];
            max_index = i;
        }
    }
    matrix.swapCols(iter, max_index);
}

void GaussSolver::nullifyCol(size_t iter) {
    Matrix &matrix = LS->matrix();
    LS->div(iter, matrix[iter][iter]);
    numb_t prevFact = 1;
    // floating point division is slower than multiplication
    for (size_t row = iter + 1; row < LS->getSize(); row++) {
        if (matrix[row][iter] == 0)
            continue;
        LS->mul(iter, matrix[row][iter] / prevFact);
        prevFact = matrix[row][iter];
        LS->sub(row, iter);
    }
}

void GaussSolver::backwardPath(Vector &root) {
    for (size_t row = LS->getSize() - 1; row + 1 != 0; row--) {
        root[row] = LS->consts(row);
        for (size_t col = row + 1; col < LS->getSize(); col++) {
            root[row] -= LS->matrix()[row][col] * root[col];
        }
    }
}

}; // namespace coma