#include "Matrix.hpp"

#include <stdlib.h>

namespace coma {

Matrix::Matrix(size_t ncols, size_t nrows) : m_rows(nrows), m_cols(ncols) {
    m_data = (numb_t *)calloc(ncols * nrows, sizeof(m_data[0]));
};

Matrix::~Matrix() { free(m_data); }

size_t Matrix::getCols() const { return m_cols; }

size_t Matrix::getRows() const { return m_rows; }

numb_t *Matrix::operator[](size_t i) {
    assert(i < m_rows);
    return m_data + m_cols * i;
};

}; // namespace coma