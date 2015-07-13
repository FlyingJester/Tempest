#include "program.hpp"
#include "routine.hpp"
#include "cpu.hpp"
#include "io.hpp"
#include "unit.hpp"

namespace Tempest {

void Program(CPU &cpu, IO &io, struct Unit &unit){

    io.skipWhitespace();
    unit.name = io.getName();

    io.emitLine(cpu.beginCode(unit));

    io.skipWhitespace();
    io.match(':');
    io.skipWhitespace();
    
    do{
        Routine<Sub, true>(cpu, io, unit);
        io.skipWhitespace();
    }while(!io.peek('.'));
    
    io.match('.');
    
    io.emitLine(cpu.writeFunctions(unit));
        
    io.emitLine(cpu.beginData(unit));
    io.emitLine(cpu.writeVariables(unit));
    
}

}
