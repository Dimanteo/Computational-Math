#pragma once
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace coma {

template <typename T> class DTRowRef {
    T *m_row;
    size_t m_len;

  public:
    class RowIterator {
        T *it_ptr;

      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T *;   // or also value_type*
        using reference = T &; // or also value_type&
        RowIterator(T *ptr) : it_ptr(ptr) {}
        reference operator*() const { return *it_ptr; }
        pointer operator->() { return it_ptr; }
        // Prefix increment
        RowIterator &operator++() {
            it_ptr++;
            return *this;
        }
        // Postfix increment
        RowIterator operator++(int) {
            RowIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        // Prefix decrement
        RowIterator &operator--() {
            it_ptr--;
            return *this;
        }
        // Postfix decrement
        RowIterator operator--(int) {
            RowIterator tmp = this;
            --(*this);
            return tmp;
        }
        friend bool operator==(const RowIterator &a, const RowIterator &b) {
            return a.it_ptr == b.it_ptr;
        };
        friend bool operator!=(const RowIterator &a, const RowIterator &b) {
            return a.it_ptr != b.it_ptr;
        };
        friend difference_type operator-(const RowIterator &lhs, const RowIterator &rhs) {
            return lhs.it_ptr - rhs.it_ptr;
        }
    };
    DTRowRef(T *row, size_t len) : m_row(row), m_len(len) {}
    T &operator[](size_t i) {
        assert(i < m_len && "index out of range");
        return m_row[i];
    }
    RowIterator begin() { return RowIterator(m_row); }
    RowIterator end() { return RowIterator(m_row + m_len); }
};

template <typename T> class DTColRef {
    T *m_colptr;
    size_t m_height;
    size_t m_step;

  public:
    class ColIterator {
        T *it_ptr;
        size_t it_step;

      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = size_t;
        using value_type = T;
        using pointer = T *;   // or also value_type*
        using reference = T &; // or also value_type&
        ColIterator(T *ptr, size_t step) : it_ptr(ptr), it_step(step) {}
        reference operator*() const { return *it_ptr; }
        pointer operator->() { return it_ptr; }
        // Prefix increment
        ColIterator &operator++() {
            it_ptr += m_step;
            return *this;
        }
        // Postfix increment
        ColIterator operator++(int) {
            ColIterator tmp = *this;
            this->it_ptr += it_step;
            return tmp;
        }
        // Prefix decrement
        ColIterator &operator--() {
            it_ptr -= it_step;
            return *this;
        }
        // Postfix decrement
        ColIterator operator--(int) {
            ColIterator tmp = this;
            this->it_ptr -= it_step;
            return tmp;
        }
        friend bool operator==(const ColIterator &a, const ColIterator &b) {
            return a.it_ptr == b.it_ptr;
        };
        friend bool operator!=(const ColIterator &a, const ColIterator &b) {
            return a.it_ptr != b.it_ptr;
        };
        friend difference_type operator-(const ColIterator &lhs, const ColIterator &rhs) {
            return (lhs.it_ptr - rhs.it_ptr) / lhs.it_step;
        }
    };

    DTColRef(T *column, size_t height, size_t step)
        : m_colptr(column), m_height(height), m_step(step) {}
    T &operator[](size_t i) {
        assert(i < m_height);
        return *(m_colptr + i * m_step);
    }
    ColIterator begin() { return ColIterator(m_colptr, m_step); }
    ColIterator end() { return ColIterator(m_colptr + m_height * m_step, m_step); }
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
    DTColRef<Data_T> getCol(size_t i);
    DTRowRef<Data_T> getRow(size_t i);
};

template <typename T>
DataTable<T>::DataTable(size_t width, size_t height) : m_width(width), m_height(height) {
    // value-initialization casts to zero-initialization for number types
    m_data = new T[width * height]();
}

template <typename T> DataTable<T>::~DataTable() { delete[](m_data); }

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

template <typename T> DTColRef<T> DataTable<T>::getCol(size_t i) {
    assert(i < m_width);
    return DTColRef<T>(m_data + i, m_height, m_width);
}

template <typename T> DTRowRef<T> DataTable<T>::getRow(size_t i) {
    assert(i < m_height);
    return DTRowRef<T>(m_data + i * m_width, m_width);
}

} // namespace coma