#pragma once

#include "Eigen/Core"

namespace coma {
using numb_t = double;
using Matrix = Eigen::MatrixXd;
using Vector = Eigen::Matrix<numb_t, Eigen::Dynamic, 1>;
template <class T> void naiveSwap(T lhs, T rhs) {
    auto tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}
}; // namespace coma