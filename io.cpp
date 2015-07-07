#include "io.hpp"
#include <cstdlib>
#include <cassert>

namespace Tempest{

bool IO::isDigit(char c){ return isHexDigit(c); }
bool IO::isDecDigit(char c){ return (c>='0' && c<='9'); }
bool IO::isHexDigit(char c){ return isDecDigit(c) || (c>='a' && c<='f') || (c>='A' && c<='F'); }
bool IO::isOctDigit(char c){ return (c>='0' && c<='7'); }
bool IO::isAlpha(char c){ return ((c&0x80) || (c>='a' && c<='z') || (c>='A' && c<='Z')); }
bool IO::isAlphaNum(char c){ return (isDigit(c) || isAlpha(c)); }
bool IO::isAlphaNumOrUnderscore(char c){ return (isAlphaNum(c) || c=='_'); }
bool IO::isWhitespace(char c){ return (c=='\n' || c=='\r' || c=='\t' || c==' '); }

uint8_t IO::asciiDecToInt(char c){ return c - '0'; }
uint8_t IO::asciiHexToInt(char c){ 
    if(c>='0' && c<='9') return c - '0';
    if(c>='a' && c<='f') return c - 'a' + 10;
    if(c>='A' && c<='F') return c - 'A' + 10;
    return 0;
}

IO::IO(FILE *in_fpt, FILE *out_fpt)
  : in(in_fpt)
  , out(out_fpt)
  , err(stderr){
    pullChar();
}

IO::~IO(){
    fclose(in);
    fclose(out);
}

void IO::abort(const std::string &msg){
    fwrite(msg.c_str(), 1, msg.size(), err);
    fprintf(err, "\n\tAt line %llu, column %llu\n", line, column);
    assert(0);
}

void IO::pullChar(){
    c_ = fgetc(in);

    if(c_=='\n'){
        line++;
        column = 0;
    }
    else if(c_=='\r');
    else if(c_=='\t') column+=4;
    else column++;

}

uint64_t IO::getNumber(){
    skipWhitespace();
    if(!isDecDigit(c_)) expected("Number");
    if(c_=='0'){
        pullChar();
        if(c_=='x' || c_=='X'){
            pullChar();
            return pullNumber<16, isHexDigit, asciiHexToInt>();
        }
        else
            return pullNumber<8, isOctDigit, asciiDecToInt>();
    }
    else
        return pullNumber<10, isDecDigit, asciiDecToInt>();
}

std::string IO::getName(){
    if(!isAlpha(c_)) expected("Name");
    std::string s;
    do{
        s+=getChar();
    }while(isAlphaNumOrUnderscore(c_));
    return s;
}

void IO::emit(const std::string& msg){
    if(msg.empty()) return;
    else fwrite(msg.c_str(), 1, msg.size(), out);
}
    
} // namespace Tempest
