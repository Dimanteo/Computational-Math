#include "LinearSystem.hpp"

namespace coma {

LinearSystem::LinearSystem(size_t size) : m_size(size), m_matrix(size, size), m_consts(size) {}
size_t LinearSystem::getSize() { return m_size; }
Matrix &LinearSystem::matrix() { return m_matrix; }
numb_t &LinearSystem::consts(size_t i) { return m_consts[i]; }

std::ostream &operator<<(std::ostream &stream, LinearSystem &LS) {
    for (size_t row = 0; row < LS.getSize(); row++) {
        for (auto num : LS.matrix().getRow(row)) {
            stream << num << " ";
        }
        stream << " = " << LS.consts(row) << "\n";
    }
    return stream;
}

void LinearSystem::add(size_t li, size_t ri) {
    for (size_t col = 0; col < m_size; col++) {
        m_matrix[li][col] += m_matrix[ri][col];
    }
    m_consts[li] += m_consts[ri];
}

void LinearSystem::sub(size_t li, size_t ri) {
    for (size_t col = 0; col < m_size; col++) {
        m_matrix[li][col] -= m_matrix[ri][col];
    }
    m_consts[li] -= m_consts[ri];
}

void LinearSystem::mul(size_t row, numb_t factor) {
    for (size_t col = 0; col < m_size; col++) {
        m_matrix[row][col] *= factor;
    }
    m_consts[row] *= factor;
}

void LinearSystem::div(size_t row, numb_t denom) {
    for (size_t col = 0; col < m_size; col++) {
        m_matrix[row][col] /= denom;
    }
    m_consts[row] /= denom;
}

}; // namespace coma