#pragma once

#include "CoMa.hpp"
#include <cstddef>

namespace coma {

class LinearSystem;

class Solver {
  public:
    LinearSystem *LS;
    Solver(LinearSystem *LS) : LS(LS) {}
    virtual Vector solve()=0;
    virtual ~Solver() = default;
};

class GaussSolver : private Solver {
    void forwardPath();
    void backwardPath(Vector &root);
    void chooseMaxCoeff(size_t iter);
    void nullifyCol(size_t iter);

  public:
    GaussSolver(LinearSystem *LS) : Solver(LS) {}
    virtual Vector solve() override;
};

} // namespace coma