#pragma once

#include "type.hpp"

#include <string>
#include <vector>

namespace Tempest {

struct Unit{
    std::string name;
    std::vector<struct Symbol<FunctionType> > Functions;
};

}
