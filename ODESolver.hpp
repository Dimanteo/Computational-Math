#pragma once
#include "CoMa.hpp"

namespace coma {

class ODESolver {
  protected:
    virtual Vector iterate(const Vector &y, numb_t step, size_t n) = 0;
  public:
    virtual std::vector<Vector>
    solve(const Vector &init, numb_t step, size_t iterations, size_t maxpoints=0);
    virtual ~ODESolver()=default;
};

};