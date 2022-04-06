#pragma once
#include "CoMa.hpp"
#include <algorithm>
#include <initializer_list>
#include <ostream>
#include <vector>

namespace coma {

struct Point {
    numb_t x;
    numb_t y;
    Point(numb_t x, numb_t y) : x(x), y(y) {}
    Point(std::initializer_list<numb_t> list) : x(*list.begin()), y(*(list.begin() + 1)) {}
};

bool operator<(const Point &lhs, const Point &rhs) { 
    if (lhs.x == rhs.x) {
        return lhs.y < rhs.y;
    }
    return lhs.x < rhs.x; 
}

/// Represents a table-defined function
class TableFunction {
    using TableTy = std::vector<Point>;
    TableTy table;
    bool sorted = false;

  public:
    void insert(const Point &p) {
        if (table.size() != 0 && p < table.back())
            sorted = false;
        table.push_back(p);
    }
    void insert(numb_t x, numb_t f) { insert({x, f}); }
    Point &get(size_t i) { return table[i]; }
    Point &operator[](size_t i) { return get(i); }
    friend std::ostream &operator<<(std::ostream &stm, TableFunction &func);
    size_t size() { return table.size(); }
    void sort() {
        if (!sorted) {
            std::sort(table.begin(), table.end());
            sorted = true;
        }
    }
};

std::ostream &operator<<(std::ostream &str, TableFunction &func) {
    for (auto point : func.table) {
        str << "x = " << point.x << " | y = " << point.y << "\n";
    }
    return str;
}

}; // namespace coma