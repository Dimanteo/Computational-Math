#pragma once
#include "CoMa.hpp"
#include <functional>
#include <vector>

namespace coma {

class FunctionMatrix {
  public:
    using ArgTy = const Vector &;
    using FuncTy = std::function<numb_t(ArgTy)>;
    using DecoratorTy = std::function<FuncTy(const FuncTy&)>;

  private:
    using FuncTableTy = std::vector<std::vector<FuncTy>>;
    FuncTableTy funcTable;

  public:
    FunctionMatrix(size_t width, size_t height);
    FuncTy &func(size_t row, size_t col) { return funcTable[row][col]; }
    Matrix at(ArgTy point);
    Vector vec_at(ArgTy point);
    size_t height() const;
    size_t width() const;
    // Creates new matrix by applying lambda to each element
    // Useful for creating Jacobi matrix with numerical derivative
    void decorate(DecoratorTy decorator, FunctionMatrix &product);
};

} // namespace coma