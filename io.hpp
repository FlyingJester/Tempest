#pragma once
#include <cstdio>
#include <cstdint>
#include <string>

#include "cpu.hpp"

namespace Tempest{

class IO{
protected:
    FILE *in, *out, *err;
    char c_;
    
    uint64_t line, column;
    
    static uint8_t asciiDecToInt(char c);
    static uint8_t asciiHexToInt(char c);
 
    template <int radix, bool(*test)(char), uint8_t(*converter)(char c)>
    uint64_t pullNumber(){
        uint64_t n = 0;
        while(test(peek())){
            n*=radix;
            n+=converter(peek());
            pullChar();
        }
        
        if(isAlpha(peek())) error("Invalid character in number");
        
        return n;
    }
    
    void pullChar();
    
public:

    IO(FILE *in_fpt, FILE *out_fpt);
    ~IO();

    static IO *Generate(const std::string &in_path, const std::string &out_path){
        FILE *i = fopen(in_path.c_str(), "r"),
            *o = fopen(out_path.c_str(), "w");
        if(i && o)
            return new IO(i, o);
        else
            return nullptr;
    }

    static bool isDigit(char c);
    static bool isDecDigit(char c);
    static bool isHexDigit(char c);
    static bool isOctDigit(char c);
    static bool isAlpha(char c);
    static bool isAlphaNum(char c);
    static bool isAlphaNumOrUnderscore(char c);
    static bool isWhitespace(char c);

    void skipWhitespace(){
        while(IO::isWhitespace(peek())) pullChar(); 
    }
    
    void abort(const std::string &msg);
    void error(const std::string &msg){abort(std::string("Error: ") + msg); } 
    void expected(const std::string &msg){abort(std::string("Expected ") + msg + " was " + peek()); }

    char peek() const { return c_; }
    bool peek(char a) const { return a==c_; }
    char getChar(){ char a = c_; pullChar(); return a; }
    void match(char a){ if (a==c_) pullChar(); else expected(std::string(1, a)); }
    uint64_t getNumber();
    std::string getName();
    
    void emit(const std::string& msg);
    inline void emitLine(const std::string& msg){ 
        if(msg.empty()) return;
        else emit(msg+'\n');
    }
    
    template<void (*call)(CPU &, IO &, struct Unit &)>
    inline void callWithPushNumber(CPU &cpu, const std::string &note, struct Unit &unit){
        emitLine(cpu.pushNumber(note));
        call(cpu, *this, unit);
    }

};

}
