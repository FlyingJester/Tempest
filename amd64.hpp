#pragma once
#include "cpu.hpp"

namespace Tempest {

class amd64 : public CPU{
protected:
    
    uint_fast8_t stack;
    
    std::string accum, accum_note;
    
    virtual std::string popNumber(const std::string &r, const std::string &note);
    virtual std::string pushNumber(const std::string &r, const std::string &note);
    
public:    

    std::string popNumber(const std::string &note) override;
    std::string pushNumber(const std::string &note) override;
    std::string loadNumber(const std::string &load, const std::string &note) override;
    std::string loadVariable(const std::string &load, const std::string &note) override;
    std::string storeVariable(const std::string &load, const std::string &note) override;
    std::string add(const std::string &note) override;
    std::string subtract(const std::string &note) override;
    
    std::string multiply(const std::string &note) override;
    std::string divide(const std::string &note) override;
    std::string remainder(const std::string &note) override;

    std::string negateBool(const std::string &note) override;
    std::string andBool(const std::string &note) override;
    std::string orBool(const std::string &note) override;
    std::string xorBool(const std::string &note) override;
    
    std::string lessThan(const std::string &note) override;    
    std::string lessThanOrEqual(const std::string &note) override;
    std::string greaterThan(const std::string &note) override;
    std::string greaterThanOrEqual(const std::string &note) override;
    std::string equal(const std::string &note) override;
    std::string notEqual(const std::string &note) override;
    
    std::string jumpZero(const std::string &label, const std::string &note) override;
    std::string ret(const std::string &note) override;
    
    std::string beginCode(const struct Unit &unit) override;
    std::string beginData(const struct Unit &unit) override;
    std::string writeVariables(const struct Unit &unit) override;
    std::string writeNanoVariables(const struct Unit &unit) override;
    std::string writeFunctions(const struct Unit &unit) override;
    
};

}
