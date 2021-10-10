#pragma once
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <cstring>

namespace coma {

template <typename T> class DTRowRef {
    T *m_row;
    size_t m_len;

  public:
    DTRowRef(T *row, size_t len) : m_row(row), m_len(len) {}
    T &operator[](size_t i) {
        assert(i < m_len && "index out of range");
        return m_row[i];
    }
};

template <typename Data_T> class DataTable {
    Data_T *m_data;
    size_t m_width;
    size_t m_height;

  public:
    DataTable(size_t ncols, size_t nrows);
    ~DataTable();
    DataTable() = delete;
    // non-copyable
    DataTable(const DataTable &) = delete;
    DataTable &operator=(const DataTable &) = delete;

    DTRowRef<Data_T> operator[](size_t row_index);
    void swapRows(size_t l, size_t r);
    void swapCols(size_t l, size_t r);

    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }
};

template <typename T>
DataTable<T>::DataTable(size_t width, size_t height) : m_width(width), m_height(height) {
    // value-initialization casts to zero-initialization for number types
    m_data = new T[width * height]();
}

template <typename T> DataTable<T>::~DataTable() {
    delete[](m_data);
}

template <typename T> DTRowRef<T> DataTable<T>::operator[](size_t row_i) {
    assert(row_i < m_height && "index out of range");
    return DTRowRef<T>(m_data + row_i * m_width, m_width);
}

template <typename T> void DataTable<T>::swapRows(size_t lrow, size_t rrow) {
    assert(lrow < m_height && "index out of range");
    assert(rrow < m_height && "index out of range");
    for (size_t col = 0; col < m_width; col++) {
        std::swap((*this)[lrow][col], (*this)[rrow][col]);
    }
}

template <typename T> void DataTable<T>::swapCols(size_t lcol, size_t rcol) {
    assert(lcol < m_width && "index out of range");
    assert(rcol < m_width && "index out of range");
    for (size_t row = 0; row < m_height; row++) {
        std::swap((*this)[row][lcol], (*this)[row][rcol]);
    }
}

} // namespace coma