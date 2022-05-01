#pragma once
#include "CoMa.hpp"
#include "ODUSolver.hpp"
#include "FunctionMatrix.hpp"

namespace coma {

class AdamsSolver : public ODUSolver {
    std::vector<numb_t> coeffs;
    FunctionMatrix *fvec;
    size_t order;
  public:
    AdamsSolver(FunctionMatrix *fvec_, size_t order);
    virtual std::vector<Vector>
      solve(const Vector &init, numb_t step, size_t iterations) override;
    void setOrder(size_t order);
  private:
    Vector iterate(const Vector &y, numb_t step, size_t n);
};

};