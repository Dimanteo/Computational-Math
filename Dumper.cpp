#include "Dumper.hpp"

namespace coma {

void Dumper::serialize(const std::vector<Vector> &data, std::ostream &str) {
    for (ssize_t row_i = 0; row_i < data[0].size(); row_i++) {
        for (const auto &vec : data) {
            str << vec(row_i) << ",";
        }
        str << "\n";
    }
}

};