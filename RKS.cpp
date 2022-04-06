#include "RKS.hpp"

namespace coma {

void ButcherTable::resize(size_t order) {
    Ctable.resize(order);
    Btable.resize(order);
    Atable.resize(order);
    for (auto &col : Atable) {
        col.resize(order);
    }
}

numb_t ButcherTable::getA(size_t row, size_t col) {
    return Atable[row - 1][col - 1];
}
numb_t ButcherTable::getB(size_t idx) {
    return Btable[idx - 1];
}
numb_t ButcherTable::getC(size_t idx) {
    return Ctable[idx - 1];
}

void ButcherTable::setA(size_t row, size_t col, numb_t val) {
    Atable[row - 1][col - 1] = val;
}
void ButcherTable::setB(size_t idx, numb_t val) {
    Btable[idx - 1] = val;
}
void ButcherTable::setC(size_t idx, numb_t val) {
    Ctable[idx - 1] = val;
}

RungeKuttSolver::RungeKuttSolver(FunctionMatrix *fvec_) 
    : order(0), table(new ButcherTable()), fvec(fvec_) {}

void RungeKuttSolver::setEquation(FunctionMatrix *func) {
    fvec = func;
}

std::vector<Vector> RungeKuttSolver::solve(const Vector &init, numb_t step, size_t iterations) {
      Vector y = init;
      std::vector<Vector> solution;
      solution.push_back(y);
      for (size_t n = 0; n < iterations; n++) {
        y = iterate(y, step, n);
        solution.push_back(y);
      }
      return solution;
    }

Vector RungeKuttSolver::iterate(const Vector &y, numb_t step, size_t n) {
    Vector next_y = y;
    calcStages(y, step, step * static_cast<numb_t>(n));
    for (size_t stage = 1; stage < order; stage++) {
    next_y += step * table->getB(stage) * getStageVal(stage);
    }
    return next_y;
}

void RungeKuttSolver::calcStages(const Vector &y, numb_t step, numb_t t) {
    for (size_t stage = 1; stage < order; stage++) {
        numb_t arg = t + table->getC(stage) * step;
        Vector vars = y;
        for (size_t s = 1; s <= stage - 1; s++) {
            vars += step * table->getA(stage, s) * getStageVal(s);
        }
        Vector joinedVec(1 + vars.size());
        joinedVec(0) = arg;
        for (ssize_t i = 1; i < joinedVec.size(); i++) {
            joinedVec(i) = vars(i - 1);
        }
        stageValues[stage] = fvec->vec_at(joinedVec);
    }
}

void RungeKuttSolver::setOrder(size_t order_) {
    order = order_;
    table->resize(order);
}

void RungeKuttSolver::setEulerMethod() {
    setOrder(2);
    table->setC(1, 0);
    table->setC(2, 1);
    table->setB(1, 0.5);
    table->setB(2, 0.5);
    table->setA(1, 1, 0);
    table->setA(1, 2, 0);
    table->setA(2, 1, 1);
    table->setA(2, 2, 0);
}

void setHeunMethod() {

}
void setForthOrder() {

}

};