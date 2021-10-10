#include "LinearSystem.hpp"

namespace coma {

LinearSystem::LinearSystem(size_t size) : m_size(size), m_matrix(size, size), m_consts(size, 1) {}
size_t LinearSystem::getSize() { return m_size; }
Matrix &LinearSystem::matrix() { return m_matrix; }
numb_t &LinearSystem::consts(size_t i) { return m_consts[0][i]; }

std::ostream &operator<<(std::ostream &stream, LinearSystem &LS) {
    for (size_t row = 0; row < LS.getSize(); row++) {
        for (auto num : LS.matrix().getRow(row)) {
            stream << num << " ";
        }
        stream << " = " << LS.consts(row) << "\n";
    }
    return stream;
}

}; // namespace coma