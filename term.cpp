#include "term.hpp"
#include "factor.hpp"
#include "cpu.hpp"
#include "io.hpp"

namespace Tempest {

void Term(CPU &cpu, IO &io, struct Unit &unit){
    Factor(cpu, io, unit);
    io.skipWhitespace();
    {
term_start:
        if(io.peek('*'))
            io.callWithPushNumber<Multiply>(cpu, "Term", unit);
        else if(io.peek('/'))
            io.callWithPushNumber<Divide>(cpu, "Term", unit);
        else if(io.peek('%'))
            io.callWithPushNumber<Remainder>(cpu, "Term", unit);
        else {
            io.skipWhitespace();
            return;
        }
        io.skipWhitespace();
        goto term_start;
    }
}

void Multiply(CPU &cpu, IO &io, struct Unit &unit){
    io.match('*');
    io.skipWhitespace();
    Term(cpu, io, unit);
    io.emitLine(cpu.multiply("Multiply"));
}

void Divide(CPU &cpu, IO &io, struct Unit &unit){
    io.match('/');
    io.skipWhitespace();
    Term(cpu, io, unit);
    io.emitLine(cpu.divide("Multiply"));
}

void Remainder(CPU &cpu, IO &io, struct Unit &unit){
    io.match('%');
    io.skipWhitespace();
    Term(cpu, io, unit);
    io.emitLine(cpu.remainder("Multiply"));
}

}
