#include "io.hpp"
#include "cpu.hpp"
#include "unit.hpp"
#include "program.hpp"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

int main(int argc, char *argv[]){

    Tempest::Unit unit;
    Tempest::IO io(stdin, stdout);
    Tempest::CPU *cpu_ptr = Tempest::CPU::createCPU("amd64");
    Tempest::CPU &cpu = *cpu_ptr;
    
    Tempest::Program(cpu, io, unit);
    
}
