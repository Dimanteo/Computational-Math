#include "FunctionMatrix.hpp"

namespace coma {

FunctionMatrix::FunctionMatrix(size_t width, size_t height)
    : funcTable(height, std::vector<FuncTy>(width, [](ArgTy) { return 0; })) {}

Matrix FunctionMatrix::at(ArgTy point) {
    Matrix matrix(height(), width());
    for (long int row = 0; row < matrix.rows(); row++) {
        for (long int col = 0; col < matrix.cols(); col++) {
            matrix(row, col) = funcTable[row][col](point);
        }
    }
    return matrix;
}

size_t FunctionMatrix::height() const { return funcTable.size(); }

size_t FunctionMatrix::width() const { return funcTable[0].size(); }

} // namespace coma