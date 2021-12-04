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

Vector::Vector(std::initializer_list<numb_t> list) : Vector(list.size()) {
    auto list_it = list.begin();
    for (size_t i = 0; i < list.size(); ++i) {
        m_vector[0][i] = *list_it;
        ++list_it;
    }
}

size_t Vector::getSize() const { return m_size; }

numb_t &Vector::operator[](size_t i) {
    assert(i < m_size);
    return m_vector[0][i];
}

numb_t &Vector::operator[](size_t i) const {
    assert(i < m_size);
    return m_vector[0][i];
}

std::ostream &operator<<(std::ostream &stream, Vector &matrix) {
    stream << matrix.m_vector;
    return stream;
}

Matrix &Matrix::operator+=(const Matrix &rhs) {
    assert(this->getHeight() == rhs.getHeight());
    assert(this->getWidth() == rhs.getWidth());
    for (size_t row = 0; row < getHeight(); row++) {
        for (size_t col = 0; col < getWidth(); col++) {
            (*this)[row][col] += rhs[row][col];
        }
    }
    return *this;
}

Matrix operator-(const Matrix &m) {
    Matrix tmp(m);
    for (size_t row = 0; row < tmp.getHeight(); row++) {
        for (auto el : tmp.getRow(row)) {
            el = -el;
        }
    }
    return tmp;
}

Matrix &Matrix::operator-=(const Matrix &rhs) {
    (*this) += -rhs;
    return *this;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    assert(lhs.getHeight() == rhs.getHeight());
    assert(lhs.getWidth() == rhs.getWidth());
    Matrix sum(lhs);
    sum += rhs;
    return sum;
}

Matrix operator-(const Matrix &rhs, const Matrix &lhs) {
    assert(lhs.getHeight() == rhs.getHeight());
    assert(lhs.getWidth() == rhs.getWidth());
    Matrix dif(lhs);
    dif -= rhs;
    return dif;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
    assert(lhs.getWidth() == rhs.getHeight());
    size_t size = lhs.getWidth();
    Matrix res(rhs.getWidth(), lhs.getHeight());
    for (size_t row = 0; row < lhs.getHeight(); row++) {
        for (size_t col = 0; col < rhs.getWidth(); col++) {
            for (size_t i = 0; i < size; i++) {
                res[row][col] += lhs[row][i] * rhs[i][col];
            }
        }
    }
    return res;
}

Vector &Vector::operator+=(Vector that) {
    assert(getSize() == that.getSize());
    for (size_t i; i < getSize(); i++) {
        (*this)[i] += that[i];
    };
    return *this;
}

Vector operator+(Vector &lhs, Vector &rhs) {
    assert(lhs.getSize() == rhs.getSize());
    Vector res(lhs);
    res += rhs;
    return res;
}

} // namespace coma