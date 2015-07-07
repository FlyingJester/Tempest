#include "amd64.hpp"
#include "cpu.hpp"

#include <algorithm>
#include <cctype>

namespace Tempest {

// Our CPU names are all in codepoints below 0x80, so it doesn't matter that we are only handling ascii.
CPU *CPU::createCPU(std::string name){
    std::for_each(name.begin(), name.end(), tolower);
    if(name=="amd64" || name=="x86_64"){
        return new amd64();
    }
    else return nullptr;
}

}
