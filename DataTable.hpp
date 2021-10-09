#pragma once
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace coma {

template <typename T> class DTRowRef {
    T *m_row;
    size_t m_len;
    size_t *m_order;

  public:
    DTRowRef(T *row, size_t *order, size_t len) : m_row(row), m_len(len), m_order(order) {}
    T &operator[](size_t i) {
        assert(i < m_len && "index out of range");
        assert(m_order);
        size_t real_i = m_order[i];
        return m_row[real_i];
    }
};

template <typename Data_T> class DataTable {
    Data_T *m_data;
    size_t m_width;
    size_t m_height;
    Data_T **m_orderRows;
    size_t *m_orderCols;

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
    m_data = new T[width *
                   height](); // value-initialization casts to zero-initialization for number types
    m_orderCols = new size_t[width];
    m_orderRows = new T *[height];
    for (size_t i = 0; i < width; i++) {
        m_orderCols[i] = i;
    }
    for (size_t i = 0; i < height; i++) {
        m_orderRows[i] = m_data + m_width * i;
    }
}

template <typename T> DataTable<T>::~DataTable() {
    delete[](m_data);
    delete[](m_orderCols);
    delete[](m_orderRows);
}

template <typename T> DTRowRef<T> DataTable<T>::operator[](size_t row_i) {
    assert(row_i < m_height && "index out of range");
    return DTRowRef<T>(m_orderRows[row_i], m_orderCols, m_width);
}

template <typename T> void DataTable<T>::swapRows(size_t l, size_t r) {
    assert(l < m_height && "index out of range");
    assert(r < m_height && "index out of range");
    std::swap(m_orderRows[l], m_orderRows[r]);
}

template <typename T> void DataTable<T>::swapCols(size_t l, size_t r) {
    assert(l < m_width && "index out of range");
    assert(r < m_width && "index out of range");
    std::swap(m_orderCols[l], m_orderCols[r]);
}

} // namespace coma