#include "amd64.hpp"
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

}
