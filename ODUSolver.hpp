#pragma once
#include "CoMa.hpp"

namespace coma {

class ODUSolver {
  public:
    virtual std::vector<Vector>
    solve(const Vector &init, numb_t step, size_t iterations) = 0;
    virtual ~ODUSolver()=default;
};

};