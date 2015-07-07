#pragma once

namespace Tempest {

class CPU;
class IO;

void Expression(CPU &cpu, IO &io, struct Unit &unit);
void Add(CPU &cpu, IO &io, struct Unit &unit);
void Subtract(CPU &cpu, IO &io, struct Unit &unit);

}
