#pragma once

#include "DataTable.hpp"

#include <cassert>
#include <cstddef>
#include <ostream>

// COmputational MAth
namespace coma {

using numb_t = double;

class Matrix {

    DataTable<numb_t> *m_data;

  public:
    Matrix(size_t ncols, size_t nrows);
    ~Matrix();
    size_t getHeight() const;
    size_t getWidth() const;
    void swapRows(size_t li, size_t ri);
    void swapCols(size_t li, size_t ri);
    DTRowRef<numb_t> operator[](size_t i);
};

std::ostream &operator<<(std::ostream &stream, Matrix &matrix);

} // namespace coma
