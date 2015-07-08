#include "amd64.hpp"
#include "unit.hpp"
#include <cassert>

namespace Tempest {

std::string amd64::popNumber(const std::string &r, const std::string &note) {
    assert(stack);
    stack--;
    if(stack<8)
        return std::string("mov " + r + ",r") + std::to_string(stack+8) + " ; " + note;
    else
        return std::string("pop ") + r + " ; " + note;
}

std::string amd64::pushNumber(const std::string &r, const std::string &note) {
    stack++;
    if(stack<9)
        return std::string("mov r") + std::to_string(stack+7) + "," + r + " ; " + note;
    else
        return std::string("push ") + r + " ; " + note;
}

std::string amd64::popNumber(const std::string &note) {
    return popNumber("rax", note);
}

std::string amd64::pushNumber(const std::string &note){
    return pushNumber("rax", note);
}

std::string amd64::loadNumber(const std::string &load, const std::string &note) {
    return std::string("mov rax,") + load + " ; " + note;
}

std::string amd64::loadVariable(const std::string &load, const std::string &note) { 
    return loadNumber(std::string(1, '[') + load + ']', note); 
}

std::string amd64::storeVariable(const std::string &load, const std::string &note) { 
    return std::string("mov [") + load + "],rax ; " + note; 
}
    
std::string amd64::add(const std::string &note){
    return popNumber("rbx", note) + "\n"\
    "add rax,rbx ;  " + note;
}

std::string amd64::subtract(const std::string &note){
    return  "mov rbx,rax ;  " + note + '\n' +
    popNumber("rax", note) + "\n"\
    "sub rax,rbx ;  " + note;
}

std::string amd64::multiply(const std::string &note){
    return popNumber("rbx", note) + "\n"\
    "imul rax,rbx ;  " + note;
}

std::string amd64::divide(const std::string &note){
    return popNumber("rbx", note) + "\n"\
    "xor rdx,rdx ; " + note + "\n"\
    "div rbx     ; " + note;
}

std::string amd64::remainder(const std::string &note){
    return popNumber("rbx") + " ; " + note + "\n"\
    "xor rdx,rdx ; " + note + "\n"\
    "div rbx     ; " + note + "\n"\
    "mov rax,rdx ; " + note;
}

std::string amd64::jumpZero(const std::string &label, const std::string &note) {
    return std::string("test rax,rax  ; ") + note + "\n"\
    "jz " + label + " ; " + note;
}

std::string amd64::beginCode(const struct Unit &unit){
    return std::string("\n; ") + unit.name + "\nsection .text\n";
}

std::string amd64::beginData(const struct Unit &unit){
    return std::string("\n; ") + unit.name + "\nsection .data\n";
}

std::string amd64::writeVariables(const struct Unit &unit){
    std::string a;
    for(uint64_t i = 0; i<unit.Functions.size(); i++){
        for(
            std::vector<struct Symbol<struct VariableType> >::const_iterator iter = unit.Functions[i].symbol.inner_variables.cbegin();
            iter!=unit.Functions[i].symbol.inner_variables.cend();
            iter++){
            a = a + iter->name + ": resb " + std::to_string(iter->symbol.element_size * iter->symbol.num_elements) + '\n';
        }
    }
    return a;
}

}
