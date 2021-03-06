#include "variable.hpp"
#include "type.hpp"
#include "cpu.hpp"
#include "io.hpp"
#include "unit.hpp"

namespace Tempest {

void Variable(CPU &cpu, IO &io, struct Unit &unit){
    const std::string name = io.getName();
    io.skipWhitespace();
    io.match(':');
    io.skipWhitespace();

    struct Symbol<struct VariableType> variable = {Type(cpu, io, unit), name};
    if(unit.Nanoroutines.empty())
        unit.Subroutines.back().symbol.inner_variables.push_back(variable);
    else
        unit.Nanoroutines.back().symbol.inner_variables.push_back(variable);

    io.skipWhitespace();

}

}
