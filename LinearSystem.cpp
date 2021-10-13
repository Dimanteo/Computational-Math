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

LinearSystem::LinearSystem(const LinearSystem &that) : LinearSystem(that.getSize()) {
    for (long int row = 0 ; row < that.m_matrix.rows(); row++) {
        for (long int col = 0; col < that.m_matrix.cols(); col++) {
            m_matrix(row, col) = that.m_matrix(row, col);
        }
    }
}

std::ostream &operator<<(std::ostream &stream, const LinearSystem &LS) {
    stream << LS.m_matrix;
    return stream;
}

void LinearSystem::swapCols(size_t li, size_t ri) {
    for (long int i = 0; i < m_matrix.rows(); i++) {
        std::swap(m_matrix(i, li), m_matrix(i, ri));
    }
}

void LinearSystem::swapRows(size_t li, size_t ri) {
    for (long int i = 0; i < m_matrix.cols(); i++) {
        std::swap(m_matrix(li, i), m_matrix(ri, i));
    }
}

void LinearSystem::add(size_t li, size_t ri) { m_matrix.row(li) += m_matrix.row(ri); }

void LinearSystem::sub(size_t li, size_t ri) { m_matrix.row(li) -= m_matrix.row(ri); }

void LinearSystem::mul(size_t row, numb_t factor) { m_matrix.row(row) *= factor; }

void LinearSystem::div(size_t row, numb_t denom) { m_matrix.row(row) /= denom; }

}; // namespace coma