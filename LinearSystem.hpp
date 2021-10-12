#pragma once

#include "CoMa.hpp"

namespace coma {
// Ax = F
class LinearSystem {
    size_t m_size;
    Matrix m_matrix;

  public:
    LinearSystem(size_t size);
    ~LinearSystem() = default;
    size_t getSize() const;
    Matrix matrix();
    Matrix matrix() const;
    numb_t &matrix(size_t row, size_t col);
    Vector consts();
    Vector consts() const;
    numb_t &consts(size_t row);
    void add(size_t li, size_t ri);
    void sub(size_t li, size_t ri);
    void mul(size_t row, numb_t factor);
    void div(size_t row, numb_t denom);
};

std::ostream &operator<<(std::ostream &stream, const LinearSystem &LS);

} // namespace coma