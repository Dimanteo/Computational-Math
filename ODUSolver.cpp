#include "ODUSolver.hpp"

namespace coma {

std::vector<Vector> ODUSolver::solve(const Vector &init,
                        numb_t step, size_t iterations, size_t maxpoints/*=0*/) {
    Vector y = init;
    Vector point(y.size() + 1);
    std::vector<Vector> solution;
    point << y, 0;
    solution.push_back(point);
    size_t skip_points = 0;
    if (maxpoints != 0) {
        skip_points = iterations / maxpoints;
    }
    size_t dump_cnt = skip_points;
    for (size_t n = 0; n < iterations; n++) {
        y = iterate(y, step, n);
        if (dump_cnt-- == 0) {
            point << y, static_cast<numb_t>(n+1) * step;
            solution.push_back(point);
            dump_cnt = skip_points;
        }
    }
    return solution;
}

};