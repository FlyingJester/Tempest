#include "declaration.hpp"
#include "expression.hpp"
#include "type.hpp"
#include "cpu.hpp"
#include "io.hpp"
#include "unit.hpp"

namespace Tempest {

void Declaration(CPU &cpu, IO &io, struct Unit &unit){
    const std::string name = io.getName();
    io.skipWhitespace();
    io.match(':');
    io.skipWhitespace();

    struct Symbol<struct VariableType> variable = {{VariableType::integral, cpu.nativeWordSize(), 1}, name};
    
    if(unit.Nanoroutines.empty())
        unit.Subroutines.back().symbol.inner_variables.push_back(variable);
    else
        unit.Nanoroutines.back().symbol.inner_variables.push_back(variable);
    Expression(cpu, io, unit);
    
    io.emitLine(cpu.storeVariable(name, "Declaration"));
    
    io.skipWhitespace();

}

}
