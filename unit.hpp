#pragma once
#include "type.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace Tempest {

struct Unit{
    std::string name;
    std::vector<struct Symbol<FunctionType> > Functions;
    uint64_t label_index;
};

}
