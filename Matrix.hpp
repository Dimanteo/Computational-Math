#ifndef MATRIX_HPP

#include <cassert>
#include <cstddef>

// COmputational MAth
namespace coma {

using numb_t = double;

class Matrix {
    size_t m_rows;
    size_t m_cols;
    numb_t *m_data;

  public:
    Matrix(size_t ncols, size_t nrows);
    ~Matrix();
    size_t getRows() const;
    size_t getCols() const;
    numb_t *operator[](size_t i);
};

}; // namespace coma

#endif // MATRIX_HPP