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
    
};

}
