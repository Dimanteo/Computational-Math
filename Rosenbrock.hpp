#pragma once
#include "ODESolver.hpp"
#include "FunctionMatrix.hpp"
#include <memory>


namespace coma {

class RosenbrockSolver : public ODESolver {
    // Method coeffs
    double a, b, c;
    std::shared_ptr<FunctionMatrix> fvec;
    std::shared_ptr<FunctionMatrix> jacobi;

    virtual Vector iterate(const Vector &y, numb_t step, size_t n) override;

  public:
    RosenbrockSolver(std::shared_ptr<FunctionMatrix> F,
                     std::shared_ptr<FunctionMatrix> J)
                     : fvec(F), jacobi(J) {}
    void setCoeffs();
    ~RosenbrockSolver()=default;
};

};