#include "Matrix.hpp"

#include <stdlib.h>

namespace coma {

std::ostream &operator<<(std::ostream &stream, Matrix &matrix) {
    for (size_t r = 0; r < matrix.getHeight(); r++) {
        for (auto num : matrix.getRow(r)) {
            stream << num << " ";
        }
        stream << '\n';
    }
    return stream;
}

} // namespace coma