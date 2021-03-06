#pragma once
#include "CoMa.hpp"
#include "ODESolver.hpp"
#include "FunctionMatrix.hpp"
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

class RungeKuttSolver : public ODESolver {
    size_t order;
    std::unique_ptr<ButcherTable> table;
    FunctionMatrix *fvec;
    std::vector<Vector> stageValues;
  public:
    RungeKuttSolver(FunctionMatrix *fvec_);
    // virtual std::vector<Vector>
    // solve(const Vector &init, numb_t step, size_t iterations, size_t maxpoints=0) override;
    void setEquation(FunctionMatrix *func);
    // Butcher tables
    void setFirstOrder();
    void setSecondOrder();
    void setThirdOrder();
    void setForthOrder();
    void setImplicit();
  private:
    void setOrder(size_t order);
    Vector iterate(const Vector &y, numb_t step, size_t n) override;
    void calcStages(const Vector &y, numb_t step, numb_t t);
    Vector getStageVal(size_t stage) const { return stageValues[stage]; }
};

};