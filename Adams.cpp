#include "Adams.hpp"

namespace coma {

AdamsSolver::AdamsSolver(FunctionMatrix *fvec_, size_t order_)
    : fvec(fvec_), order(order_) {
    setOrder(order_);
}

// std::vector<Vector>
// AdamsSolver::solve(const Vector &init, numb_t step, size_t iterations,
//                     size_t maxpoints/*=0*/) {
//     Vector y = init;
//     std::vector<Vector> solution;
//     solution.push_back(y);
//     for (size_t n = 0; n < iterations; n++) {
//         y = iterate(y, step, n);
//         solution.push_back(y);
//     }
//     return solution;
// }

Vector AdamsSolver::iterate(const Vector &y, numb_t step, size_t n) {
    Vector next_y = y;
    numb_t time = static_cast<numb_t>(n) * step;
    for (size_t i = 0; i < order; i++) {
        time -= step * static_cast<numb_t>(i);
        Vector arg(y.size() + 1);
        arg << time, y;
        next_y += step * coeffs[i] * fvec->vec_at(arg);
    }
    return next_y;
}

void AdamsSolver::setOrder(size_t order_) {
    coeffs.resize(order_);
    order = order_;
    switch (order)
    {
    case 2:
        coeffs[0] = 3.0 / 2.0;
        coeffs[1] = -1.0 / 2.0;
        break;
    case 3:
        coeffs[0] = 23.0 / 12.0;
        coeffs[1] = -16.0 / 12;
        coeffs[2] = 5.0 / 12.0;
        break;
    case 4:
        coeffs[0] = 55.0 / 24;
        coeffs[1] = -59.0 / 24.0;
        coeffs[2] = 37.0 / 24.0;
        coeffs[3] = -9.0 / 24.0;
        break;
    case 1:
    default:
        order = 1;
        coeffs.resize(1);
        coeffs[0] = 1;
        break;
    }
}

};