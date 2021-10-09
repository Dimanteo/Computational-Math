#include "Matrix.hpp"

#include <stdlib.h>

namespace coma {

Matrix::Matrix(size_t width, size_t height) { m_data = new DataTable<numb_t>(width, height); }

Matrix::~Matrix() { delete (m_data); }

size_t Matrix::getHeight() const { return m_data->getHeight(); }

size_t Matrix::getWidth() const { return m_data->getWidth(); }

DTRowRef<numb_t> Matrix::operator[](size_t i) { return (*m_data)[i]; }

std::ostream &operator<<(std::ostream &stream, Matrix &matrix) {
    for (size_t r = 0; r < matrix.getHeight(); r++) {
        for (size_t c = 0; c < matrix.getWidth(); c++) {
            stream << matrix[r][c] << " ";
        }
        stream << '\n';
    }
    return stream;
}

void Matrix::swapRows(size_t li, size_t ri) { m_data->swapRows(li, ri); }

void Matrix::swapCols(size_t li, size_t ri) { m_data->swapCols(li, ri); }

} // namespace coma