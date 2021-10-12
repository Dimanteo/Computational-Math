#include "LinearSystem.hpp"

namespace coma {

LinearSystem::LinearSystem(size_t size) : m_size(size), m_matrix(Matrix::Zero(size, size + 1)) {}
size_t LinearSystem::getSize() const { return m_size; }
Matrix LinearSystem::matrix() { return m_matrix.leftCols(m_size); }
Vector LinearSystem::consts() { return m_matrix.rightCols(1); }
Matrix LinearSystem::matrix() const { return m_matrix.leftCols(m_size); }
Vector LinearSystem::consts() const { return m_matrix.rightCols(1); }
numb_t &LinearSystem::matrix(size_t row, size_t col) { return m_matrix.leftCols(m_size)(row, col); }
numb_t &LinearSystem::consts(size_t row) { return m_matrix.rightCols(1)(row); }

std::ostream &operator<<(std::ostream &stream, const LinearSystem &LS) {
    stream << LS.matrix();
    return stream;
}

void LinearSystem::add(size_t li, size_t ri) { m_matrix.row(li) += m_matrix.row(ri); }

void LinearSystem::sub(size_t li, size_t ri) { m_matrix.row(li) -= m_matrix.row(ri); }

void LinearSystem::mul(size_t row, numb_t factor) { m_matrix.row(row) *= factor; }

void LinearSystem::div(size_t row, numb_t denom) { m_matrix.row(row) /= denom; }

}; // namespace coma