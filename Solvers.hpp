#pragma once

#include "CoMa.hpp"
#include <cstddef>

namespace coma {

class LinearSystem;

class BaseSolver {
  public:
    LinearSystem *LS;
    BaseSolver(LinearSystem *LS) : LS(LS) {}
};

class DirectSolver : public BaseSolver {
  public:
    DirectSolver(LinearSystem *LS) : BaseSolver(LS) {}
    virtual Vector solve() = 0;
    virtual ~DirectSolver() = default;
};

class IterativeSolver : public BaseSolver {
    // X_k+1 = B*X_k + F
    Matrix B;
    Vector F;
    virtual void calcCoeffs() = 0;
    virtual size_t estimateIterations(numb_t precision) = 0;
    virtual Vector iterate(size_t it_number) = 0;
  public:
    IterativeSolver(LinearSystem *LS) : BaseSolver(LS) {}
    virtual Vector solve(numb_t precision);
    virtual ~IterativeSolver() = default;
};

class GaussSolver : public DirectSolver {
    void forwardPath();
    void backwardPath(Vector &root);
    void chooseMaxCoeff(size_t iter);
    void nullifyCol(size_t iter);

  public:
    GaussSolver(LinearSystem *LS) : DirectSolver(LS) {}
    virtual Vector solve() override;
};

class SeidelSolver : public IterativeSolver {
    // X_k+1 = B*X_k + F
    Matrix B;
    Vector F;
    void decompose(Matrix &L, Matrix &D, Matrix &U);
    virtual size_t estimateIterations(numb_t precision) override;
    virtual Vector iterate(size_t it_number) override;
    virtual void calcCoeffs() override;
  public:
    SeidelSolver(LinearSystem *LS) : IterativeSolver(LS) {}
};

} // namespace coma