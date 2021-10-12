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
    Matrix matrix = LS->matrix();
    numb_t max = matrix(iter, iter);
    size_t max_index = iter;
    for (size_t i = iter; i < LS->getSize(); i++) {
        if (fabs(max) < fabs(matrix(iter, i))) {
            max = matrix(iter, i);
            max_index = i;
        }
    }
    LS->swapCols(iter, max_index);
}

void GaussSolver::nullifyCol(size_t iter) {
    Matrix matrix = LS->matrix();
    LS->div(iter, matrix(iter, iter));
    numb_t prevFact = 1;
    // floating point division is slower than multiplication
    for (size_t row = iter + 1; row < LS->getSize(); row++) {
        if (matrix(row, iter) == 0)
            continue;
        LS->mul(iter, matrix(row, iter) / prevFact);
        prevFact = matrix(row, iter);
        LS->sub(row, iter);
    }
}

void GaussSolver::backwardPath(Vector &root) {
    for (size_t row = LS->getSize() - 1; row + 1 != 0; row--) {
        root(row) = LS->consts(row);
        for (size_t col = row + 1; col < LS->getSize(); col++) {
            root(row) -= LS->matrix(row, col) * root(col);
        }
    }
}

Vector IterativeSolver::solve(numb_t precision) {
    calcCoeffs();
    size_t it_number = estimateIterations(precision);
    return iterate(it_number);
}

void SeidelSolver::calcCoeffs() {
    Matrix A = LS->matrix();
    Matrix L = Matrix::Zero(A.rows(), A.cols()); // lower
    Matrix D = Matrix::Zero(A.rows(), A.cols()); // diag
    Matrix U = Matrix::Zero(A.rows(), A.cols()); // upper
    decompose(L, D, U);
    // X_k+1 = B*X_k + F
    Matrix tmp = (L + D).adjoint();
    B = -tmp * U;
    F = tmp * LS->consts();
}

void SeidelSolver::decompose(Matrix &L, Matrix &D, Matrix &U) {
    Matrix A = LS->matrix();
    for (long int row = 0; row < A.rows(); row++) {
        for (long int col = 0; col < A.cols(); col++) {
            if (col < row) {
                L(row, col) = A(row, col);
            } else if (col > row) {
                U(row, col) = A(row, col);
            } else { // diag
                D(row, col) = A(row, col);
            }
        }
    }
}

size_t SeidelSolver::estimateIterations(numb_t precision) {
    auto q = B.norm();
    assert(q < 1);
    size_t k = static_cast<size_t>(std::ceil(log(precision * (1 - q) / F.norm()) / log(q))) + 1;
    return k;
}

Vector SeidelSolver::iterate(size_t it_number) {
    Vector solution = Vector::Zero(LS->getSize());
    for (;it_number != 0; it_number--) {
        solution = B * solution + F;
    }
    return solution;
}

}; // namespace coma