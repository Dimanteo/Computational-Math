#include "CoMa.hpp"
#include "fstream"

namespace coma {

class Dumper {
public:
    static void serialize(const std::vector<Vector> &data, std::ostream &str);
};

};