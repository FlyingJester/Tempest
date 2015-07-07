#include "type.hpp"
#include "cpu.hpp"
#include "io.hpp"

namespace Tempest {

struct VariableType Type(CPU &cpu, IO &io, struct Unit &unit){
    
    if(io.peek('{')){
        int current_bracket = 1;
        /* TODO: Inner analysis of complexes */
        while(current_bracket!=0){
            io.getChar();
            if(io.peek()=='}') current_bracket--;
            else if (io.peek()=='{') current_bracket++;
        }
        return {VariableType::complex, cpu.pointerSize(), 2};
    }
    else {
        const uint64_t u = io.getNumber();
        io.skipWhitespace();
        return Type(cpu, io, unit, u);
    }
}

struct VariableType Type(CPU &cpu, IO &io, struct Unit &unit, uint64_t size){

    if(io.peek('[')){
        io.match('[');
        io.skipWhitespace();
            
        const struct VariableType inner_type = Type(cpu, io, unit);
            
        io.match(']');
        io.skipWhitespace();
            
        if(inner_type.category == VariableType::integral)
            return {VariableType::scalar, inner_type.element_size, size};
        else
            return {VariableType::scalar, cpu.pointerSize(), size};
    }
    else{
        io.match('(');
        io.skipWhitespace();
        io.match(')');
        io.skipWhitespace();
        
        return {VariableType::integral, size, 1};
    }
    
}

} // namespace Tempest
