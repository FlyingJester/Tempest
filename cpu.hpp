#pragma once
#include <string>

namespace Tempest {

// Note that the CPU interface is not thread safe.

class CPU{
protected:
    
public:

    virtual std::string popNumber(const std::string &note) = 0;
    virtual std::string pushNumber(const std::string &note) = 0;
    virtual std::string loadNumber(uint64_t i, const std::string &note){ return loadNumber(std::to_string(i), note); }
    
    virtual std::string loadNumber(const std::string &load, const std::string &note) = 0;
    virtual std::string loadVariable(const std::string &load, const std::string &note) = 0;
    virtual std::string storeVariable(const std::string &load, const std::string &note) = 0;

    virtual std::string add(const std::string &note) = 0;
    virtual std::string subtract(const std::string &note) = 0;
    virtual std::string multiply(const std::string &note) = 0;
    virtual std::string divide(const std::string &note) = 0;
    virtual std::string remainder(const std::string &note) = 0;
    
    virtual std::string negateBool(const std::string &note) = 0;
    virtual std::string andBool(const std::string &note) = 0;
    virtual std::string orBool(const std::string &note) = 0;
    virtual std::string xorBool(const std::string &note) = 0;
    virtual std::string nandBool(const std::string &note){
        return andBool(note) + '\n' +
        negateBool(note);
    }
    
    virtual std::string lessThan(const std::string &note) = 0;
    virtual std::string greaterThan(const std::string &note) = 0;
    virtual std::string equal(const std::string &note) = 0;
    
    virtual std::string lessThanOrEqual(const std::string &note){
        return greaterThan(note) + '\n' +
        negateBool(note);
    }
    
    virtual std::string greaterThanOrEqual(const std::string &note){
        return lessThan(note) + '\n' +
        negateBool(note);
    }
    
    virtual std::string notEqual(const std::string &note){
        return equal(note) + '\n' +
        negateBool(note);
    }
    
    virtual unsigned pointerSize() const { return 8; }
    virtual unsigned nativeWordSize() const { return 8; }
    virtual std::string jumpZero(const std::string &label, const std::string &note) = 0;
    virtual std::string ret(const std::string &note) = 0;
    
    virtual std::string label(const std::string &l, const std::string &){
        return l + ':';
    }
    
    virtual std::string beginCode(const struct Unit &unit) = 0;
    virtual std::string beginData(const struct Unit &unit) = 0;
    virtual std::string writeVariables(const struct Unit &unit) = 0;
    virtual std::string writeNanoVariables(const struct Unit &unit) = 0;
    virtual std::string writeFunctions(const struct Unit &unit) = 0;
    
    static CPU *createCPU(std::string name);

};

}
