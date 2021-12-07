#pragma once

#include "CoMa.hpp"
#include <FunctionMatrix.hpp>
#include <cstddef>
#include <memory>

namespace coma {

class LinearSystem;

class BaseLinearSolver {
  public:
    LinearSystem *LS;
    BaseLinearSolver(LinearSystem *LS) : LS(LS) {}
    virtual Vector solve() = 0;
};

class BaseIterativeSolver {
  public:
    virtual Vector solve(const Vector &base, numb_t precision) = 0;
};

class DirectSolver : public BaseLinearSolver {
  public:
    DirectSolver(LinearSystem *LS) : BaseLinearSolver(LS) {}
    virtual ~DirectSolver() = default;
};

class SimpleIterationSolver : public BaseLinearSolver {
    // X_k+1 = B*X_k + F
    Matrix B;
    Vector F;
    virtual void calcCoeffs() = 0;
    virtual size_t estimateIterations(numb_t precision) = 0;
    virtual Vector iterate(size_t it_number) = 0;

  public:
    SimpleIterationSolver(LinearSystem *LS) : BaseLinearSolver(LS) {}
    virtual Vector solve(numb_t precision);
    virtual Vector solve() override { return solve(1e-4); }
    virtual ~SimpleIterationSolver() = default;
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

class SeidelSolver : public SimpleIterationSolver {
    // X_k+1 = B*X_k + F
    Matrix B;
    Vector F;
    void decompose(Matrix &L, Matrix &D, Matrix &U);
    virtual size_t estimateIterations(numb_t precision) override;
    virtual Vector iterate(size_t it_number) override;
    virtual void calcCoeffs() override;

  public:
    SeidelSolver(LinearSystem *LS) : SimpleIterationSolver(LS) {}
};

/// Non Linear solvers

class NewtonSolver : BaseIterativeSolver {
    /// X_(n+1) = X_n + J^{-1}(x_n) * F(x_n)
    std::unique_ptr<FunctionMatrix> J;
    std::unique_ptr<FunctionMatrix> F;

  public:
    NewtonSolver(size_t dimension);
    virtual ~NewtonSolver() = default;
    Vector solve(const Vector &base, numb_t precision) override;
    FunctionMatrix *jacobian() { return J.get(); }
    FunctionMatrix *function() { return F.get(); }
};

} // namespace coma