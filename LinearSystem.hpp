#pragma once

#include "Matrix.hpp"

namespace coma {
// Ax = F
class LinearSystem {
    size_t m_size;
    Matrix m_matrix;
    Vector m_consts;

  public:
    LinearSystem(size_t size);
    ~LinearSystem() = default;
    size_t getSize();
    Matrix &matrix();
    numb_t &consts(size_t i);
    void add(size_t li, size_t ri);
    void sub(size_t li, size_t ri);
    void mul(size_t row, numb_t factor);
    void div(size_t row, numb_t denom);
};

std::ostream &operator<<(std::ostream &stream, LinearSystem &LS);

} // namespace coma