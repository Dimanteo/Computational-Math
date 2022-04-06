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

Vector FunctionMatrix::vec_at(ArgTy point) {
    Matrix matr = at(point);
    if (height() == 1) {
        Vector vec(width());
        for (size_t c = 0; c < width(); c++) {
            vec(c) = matr(0, c);
        }
        return vec;
    } else if (width() == 1) {
        Vector vec(height());
        for (size_t r = 0; r < height(); r++) {
            vec(r) = matr(r, 0);
        }
        return vec;
    } else {
        assert(0 && "Invalid dimensions for function vector");
    }
    return Vector();
}

size_t FunctionMatrix::height() const { return funcTable.size(); }

size_t FunctionMatrix::width() const { return funcTable[0].size(); }

} // namespace coma