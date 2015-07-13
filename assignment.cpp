#include "assignment.hpp"
#include "expression.hpp"
#include "cpu.hpp"
#include "io.hpp"

namespace Tempest {

void Assignment(CPU &cpu, IO &io, struct Unit &unit, const std::string &to){
    io.match('=');
    io.skipWhitespace();
    
    Expression(cpu, io, unit);
    
    io.emitLine(cpu.storeVariable(to, "Assignment"));
    
}

}