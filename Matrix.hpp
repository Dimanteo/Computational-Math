#pragma once

#include "DataTable.hpp"

#include <cassert>
#include <cstddef>
#include <ostream>
#include <initializer_list>

// COmputational MAth
namespace coma {

using numb_t = double;

class Matrix : public DataTable<numb_t> {
  public:
    Matrix(size_t ncols, size_t nrows) : DataTable<numb_t>(ncols, nrows){};
    Matrix &operator+=(const Matrix &rhs);
    Matrix &operator-=(const Matrix &rhs);
};

std::ostream &operator<<(std::ostream &stream, Matrix &matrix);

class Vector {
    size_t m_size;
    Matrix m_vector;

  public:
    Vector(size_t size);
    Vector(std::initializer_list<numb_t> list);
    Vector(const Vector &that) : m_size(that.getSize()), m_vector(that.m_vector) {};
    size_t getSize() const;
    numb_t &operator[](size_t i);
    numb_t &operator[](size_t i) const;
    friend std::ostream &operator<<(std::ostream &stream, Vector &matrix);
    friend Vector operator+(Vector &lhs, Vector &rhs);
    Vector &operator+=(Vector that);
};

Matrix operator-(const Matrix &m);
Matrix operator+(const Matrix &lhs, const Matrix &rhs);
Matrix operator-(const Matrix &rhs, const Matrix &lhs);
Matrix operator*(const Matrix &lhs, const Matrix &rhs);

} // namespace coma
