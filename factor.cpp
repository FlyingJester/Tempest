#include "expression.hpp"
#include "cpu.hpp"
#include "io.hpp"

namespace Tempest {

// <factor> ::= <number> | <variable> | <call> | <access> | '(' <expression> ')'

void Factor(CPU &cpu, IO &io, struct Unit &unit){
    if(io.isDigit(io.peek())){
        io.emitLine(cpu.loadNumber(io.getNumber(), "Factor"));
        io.skipWhitespace();
    }
    else if(io.peek('(')){
        io.match('(');
        io.skipWhitespace();
        Expression(cpu, io, unit);
        io.match(')');
        io.skipWhitespace();
    }
    else{
        const std::string name = io.getName();
        io.skipWhitespace();
        cpu.loadVariable(name, "Factor");
//        assert(false && "Access and Call not yet implemented");
    }
}

}
