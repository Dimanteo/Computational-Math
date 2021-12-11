#pragma once
#include "TableFunction.hpp"

namespace coma {

class Integrator {
  public:
    static numb_t trapezoidal(TableFunction &f, size_t step = 1);
    static numb_t simpson(TableFunction &f);
    static numb_t rungeDeviation(numb_t integral, numb_t sparse_int, size_t step, size_t power);
};

} // namespace coma