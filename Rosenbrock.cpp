#include "Rosenbrock.hpp"

namespace coma {

Vector RosenbrockSolver::iterate(const Vector &y, numb_t step, size_t n) {
    Vector u(y.size() + 1);
    numb_t time = step * static_cast<numb_t>(n);
    u << time, y;
    Vector right = y + c * step * fvec->vec_at(u);
    Vector arg(right.size() + 1);
    arg << time, right;
    right = step * fvec->vec_at(arg);
    Matrix J = jacobi->at(u);
    Matrix E = Matrix::Zero(y.size(), y.size());
    for (int i = 0; i < E.rows(); i++) {
        E(i, i) = 1;
    }
    Matrix linSys = E - a * step * J - b * step * step *J * J;
    Vector next_y = y + step * linSys.inverse() * right;
    return next_y;
}

void RosenbrockSolver::setCoeffs() {
    // Third order implicit
    a = 1.077;
    b = -0.372;
    c = -0.577;
}

};