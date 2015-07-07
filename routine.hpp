#pragma once
#include "type.hpp"
#include "variable.hpp"
#include "declaration.hpp"
#include "cpu.hpp"
#include "io.hpp"
#include "unit.hpp"

namespace Tempest {

enum RoutineType{Sub, Nano};

template<RoutineType RT, bool Prefixed>
void Routine(CPU &cpu, IO &io, struct Unit &unit);

/* Small dispatch templated to differentiate nanoroutines and subroutines */
template<RoutineType RT>
void Identifier(CPU &cpu, IO &io, struct Unit &unit){
    const std::string name = io.getName();
    io.skipWhitespace();
    if(RT==Nano && name=="nanoroutine")
        Routine<Nano, false> (cpu, io, unit);
    else{
        if(name=="assigned")
            Declaration(cpu, io, unit);
        else if(name=="unassigned")
            Variable(cpu, io, unit);
       // else
       //     Assignment(cpu, io, unit, name);
        io.match(';');
        io.skipWhitespace();
    }
}

template<RoutineType RT, bool Prefixed>
void Routine(CPU &cpu, IO &io, struct Unit &unit){
    io.skipWhitespace();
    if(Prefixed && io.getName() != ((RT==Nano)?"nanoroutine":"subroutine")) io.expected("Declarator `subroutine'");

    io.skipWhitespace();
    struct VariableType return_type = Type(cpu, io, unit);
    
    const std::string name = io.getName();
    io.emitLine(cpu.label(name, "subroutine"));

    struct Symbol<FunctionType> symbol = {{return_type, {}, {}}, name};
    unit.Functions.push_back(symbol);

    io.match(':');
    io.skipWhitespace();

    do{
        Identifier<(RT==Sub)?Nano:Sub>(cpu, io, unit);
        io.skipWhitespace();
    }while(!io.peek('.'));
    
    io.match('.');
    
    /* TODO: Write variables */
    if(RT!=Sub)
        unit.Functions.pop_back();
    
}

}
