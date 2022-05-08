#pragma once
#include "CoMa.hpp"
#include "ODESolver.hpp"
#include "FunctionMatrix.hpp"

namespace coma {

class AdamsSolver : public ODESolver {
    std::vector<numb_t> coeffs;
    FunctionMatrix *fvec;
    size_t order;
  public:
    AdamsSolver(FunctionMatrix *fvec_, size_t order);
    void setOrder(size_t order);
  private:
    Vector iterate(const Vector &y, numb_t step, size_t n) override;
};

};