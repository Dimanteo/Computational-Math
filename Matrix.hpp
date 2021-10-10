#pragma once

#include "DataTable.hpp"

#include <cassert>
#include <cstddef>
#include <ostream>

// COmputational MAth
namespace coma {

using numb_t = double;

class Matrix : public DataTable<numb_t> {
  public:
    Matrix(size_t ncols, size_t nrows) : DataTable<numb_t>(ncols, nrows){};
};

std::ostream &operator<<(std::ostream &stream, Matrix &matrix);

} // namespace coma
