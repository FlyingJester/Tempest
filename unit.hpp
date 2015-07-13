#pragma once
#include "type.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace Tempest {

struct Unit{

    typedef std::vector<struct Symbol<FunctionType> > function_holder;

    std::string name;
    function_holder Subroutines, Nanoroutines;
    uint64_t label_index;
};

}
