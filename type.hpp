#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace Tempest {

class CPU;
class IO;

struct VariableType {
    enum Category {integral, scalar, complex} category;
    uint64_t element_size, num_elements;
};

template<typename T>
struct Symbol{
    T symbol;
    std::string name;
};

/* Used for nanoroutines and subroutines */
struct FunctionType {
    struct VariableType return_type;
    std::vector<struct VariableType> arguments;
    std::vector<struct Symbol<struct VariableType> > inner_variables;
};

struct VariableType Type(CPU &cpu, IO &io, struct Unit &unit);
/* Note that this version does not work with complexes */
struct VariableType Type(CPU &cpu, IO &io, struct Unit &unit, uint64_t size);

}
