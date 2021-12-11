#include "Integrator.hpp"

namespace coma {
numb_t Integrator::trapezoidal(TableFunction &f, size_t step /*=1*/) {
    numb_t sum = 0;
    f.sort();
    for (size_t i = 0; i < f.size() - step; i += step) {
        sum += 0.5 * (f[i + step].x - f[i].x) * (f[i + step].y + f[i].y);
    }
    return sum;
}

numb_t Integrator::simpson(TableFunction &f) {
    numb_t sum = 0;
    numb_t h = f[1].x - f[0].x;
    f.sort();
    for (size_t i = 1; i < f.size() - 1; i += 2) {
        sum += (f[i - 1].y + 4 * f[i].y + f[i + 1].y);
    }
    return sum * h / 3.0;
}

numb_t Integrator::rungeDeviation(numb_t integral, numb_t sparse_int, size_t step, size_t power) {
    return (integral - sparse_int) /
           (pow(static_cast<double>(step), static_cast<double>(power)) - 1);
}

} // namespace coma