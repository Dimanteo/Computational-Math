#include <CoMa.hpp>
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
};

class RungeKuttSolver {
    size_t order;
    std::unique_ptr<ButcherTable> table;
    FunctionMatrix *fvec;
    std::vector<Vector> stageValues;
  public:
    RungeKuttSolver(FunctionMatrix *fvec_);
    std::vector<Vector> solve(const Vector &init, numb_t step, size_t iterations);
    void setEquation(FunctionMatrix *func);
    // Butcher tables
    void setEulerMethod(); // 2 order
    void setHeunMethod();  // 3 order
    void setForthOrder();  // 4 order
  private:
    void setOrder(size_t order);
    Vector iterate(const Vector &y, numb_t step, size_t n);
    void calcStages(const Vector &y, numb_t step, numb_t t);
    Vector getStageVal(size_t stage) const { return stageValues[stage]; }
};

};