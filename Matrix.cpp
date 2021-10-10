#include "Matrix.hpp"

#include <stdlib.h>

namespace coma {

std::ostream &operator<<(std::ostream &stream, Matrix &matrix) {
    for (size_t r = 0; r < matrix.getHeight(); r++) {
        for (auto num : matrix.getRow(r)) {
            stream << num << " ";
        }
        stream << '\n';
    }
    return stream;
}

Vector::Vector(size_t size) : m_size(size), m_vector(size, 1) {}

size_t Vector::getSize() const { return m_size; }

numb_t &Vector::operator[](size_t i) {
    assert(i < m_size);
    return m_vector[0][i];
}

std::ostream &operator<<(std::ostream &stream, Vector &matrix) {
    stream << matrix.m_vector;
    return stream;
}

} // namespace coma