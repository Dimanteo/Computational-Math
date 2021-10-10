#pragma once

#include "Matrix.hpp"

namespace coma {

class LinearSystem : public Matrix {
    size_t dimension;

    public:
    LinearSystem(size_t dimension) : Matrix(dimension + 1, dimension) {};
};

}