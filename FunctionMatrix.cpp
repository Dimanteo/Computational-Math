#include "FunctionMatrix.hpp"

namespace coma {

FunctionMatrix::FunctionMatrix(size_t width, size_t height)
    : m_matrix(Matrix::Zero(height, width)),
      funcTable(height, std::vector<FuncTy>(width, [](ArgTy) { return 0; })) {}

void FunctionMatrix::calculate(ArgTy point) {
    for (long int row = 0; row < m_matrix.rows(); row++) {
        for (long int col = 0; col < m_matrix.cols(); col++) {
            m_matrix(row, col) = funcTable[row][col](point);
        }
    }
}
} // namespace coma