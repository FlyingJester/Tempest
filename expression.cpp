#include "expression.hpp"
#include "term.hpp"
#include "io.hpp"
#include "cpu.hpp"

namespace Tempest {

void Expression(CPU &cpu, IO &io, struct Unit &unit){
    Term(cpu, io, unit);
    io.skipWhitespace();
    {
expression_start:
        if(io.peek('+'))
            io.callWithPushNumber<Add>(cpu, "Expression", unit);
        else if(io.peek('-'))
            io.callWithPushNumber<Subtract>(cpu, "Expression", unit);
        else {
            io.skipWhitespace();
            return;
        }
        io.skipWhitespace();
        goto expression_start;
    }
}

void Add(CPU &cpu, IO &io, Unit &unit){
    io.match('+');
    io.skipWhitespace();
    Term(cpu, io, unit);
    io.emitLine(cpu.add("Add"));
}

void Subtract(CPU &cpu, IO &io, Unit &unit){
    io.match('-');
    io.skipWhitespace();
    Term(cpu, io, unit);
    io.emitLine(cpu.subtract("Subtract"));
}

}
