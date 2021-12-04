#pragma once
#include "CoMa.hpp"
#include <functional>
#include <vector>

namespace coma {

class FunctionMatrix {
    Matrix m_matrix;

  public:
    using ArgTy = const Vector &;
    using FuncTy = std::function<numb_t(ArgTy)>;

  private:
    using FuncTableTy = std::vector<std::vector<FuncTy>>;
    FuncTableTy funcTable;

  public:
    FunctionMatrix(size_t width, size_t height);
    FuncTy &func(size_t row, size_t col) { return funcTable[row][col]; }
    void calculate(ArgTy point);
    friend std::ostream &operator<<(std::ostream &stream, const FunctionMatrix &FM) {
        stream << FM.m_matrix;
        return stream;
    }
};

} // namespace coma