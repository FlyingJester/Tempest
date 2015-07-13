#pragma once
#include <string>

namespace Tempest {

class CPU;
class IO;

void Assignment(CPU &cpu, IO &io, struct Unit &unit, const std::string &to);

}