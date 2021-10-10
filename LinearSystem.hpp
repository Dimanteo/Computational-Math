#pragma once

#include "Matrix.hpp"

namespace coma {
// Ax = F
class LinearSystem {
    size_t m_size;
    Matrix m_matrix;
    Matrix m_consts;

  public:
    LinearSystem(size_t size);
    ~LinearSystem() = default;
    size_t getSize();
    Matrix &matrix();
    numb_t &consts(size_t i);
};

std::ostream &operator<<(std::ostream &stream, LinearSystem &LS);

} // namespace coma