#include "Dumper.hpp"

namespace coma {

void Dumper::serialize(const std::vector<Vector> &data, std::ostream &str, int precision/*=8*/) {
    str.precision(precision);
    for (ssize_t row_i = 0; row_i < data[0].size(); row_i++) {
        size_t cnt = 0;
        for (const auto &vec : data) {
            str << vec(row_i);
            cnt++;
            if (cnt != data.size()) {
                str << ",";
            }
        }
        str << "\n";
    }
}

};