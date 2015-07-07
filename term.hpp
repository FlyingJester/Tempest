#pragma once

namespace Tempest {

class CPU;
class IO;

void Term(CPU &cpu, IO &io, struct Unit &unit);
void Multiply(CPU &cpu, IO &io, struct Unit &unit);
void Divide(CPU &cpu, IO &io, struct Unit &unit);
void Remainder(CPU &cpu, IO &io, struct Unit &unit);

}
