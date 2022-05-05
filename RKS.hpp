#pragma once
#include "CoMa.hpp"
#include "ODUSolver.hpp"
#include "FunctionMatrix.hpp"
#include "Solvers.hpp"
#include <vector>
#include <memory>

namespace coma {

class ButcherTable {
    std::vector<std::vector<numb_t>> Atable;
    std::vector<numb_t> Btable;
    std::vector<numb_t> Ctable;
  public:
    void setA(size_t row, size_t col, numb_t val);
    void setB(size_t idx, numb_t val);
    void setC(size_t idx, numb_t val);
    numb_t getA(size_t row, size_t col);
    numb_t getB(size_t idx);
    numb_t getC(size_t idx);
    void resize(size_t order);
    void setZero();
};

class RungeKuttBase : public ODUSolver {
  public:
    RungeKuttBase(FunctionMatrix *fvec_);
    virtual std::vector<Vector>
      solve(const Vector &init, numb_t step, size_t iterations) override;
  protected:
    size_t order;
    std::unique_ptr<ButcherTable> table;
    std::shared_ptr<FunctionMatrix> fvec;
    std::vector<Vector> stageValues;

    virtual void calcStages(const Vector &y, numb_t step, numb_t t) = 0;
    void setOrder(size_t order);
    Vector getStageVal(size_t stage) const { return stageValues[stage]; };
    Vector iterate(const Vector &y, numb_t step, size_t n);
};

/// Explicit Runge-Kutta method
class RungeKuttSolver : public RungeKuttBase {
  public:
    RungeKuttSolver(FunctionMatrix *fvec_) : RungeKuttBase(fvec_) {};
    // Butcher tables
    void setFirstOrder();
    void setSecondOrder();
    void setThirdOrder();
    void setForthOrder();
    void setImplicit() { setSecondOrder(); }
  private:
    void calcStages(const Vector &y, numb_t step, numb_t t) override;
};

/// Implicit Runge-Kutta method
class RungeKuttImplicit : public RungeKuttBase {
    std::unique_ptr<NewtonSolver> sysSolver;
    void calcStages(const Vector &y, numb_t step, numb_t t) override;
  public:
    RungeKuttImplicit(FunctionMatrix *fvec_, FunctionMatrix *jacobi);
    virtual ~RungeKuttImplicit()=default;
};

};