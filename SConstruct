import os

environment = Environment(ENV = os.environ)

environment.Append(
    CCFLAGS = " -Wall -Wextra -pedantic -Werror -Os -g ",
    CXXFLAGS = " -std=c++11 -fno-exceptions -fno-rtti ",
    CFLAGS = " -ansi ",
    LINKFLAGS = " -g ")

libtempest = environment.StaticLibrary("tempest", 
    ["program.cpp", "type.cpp", "declaration.cpp", "variable.cpp", "assignment.cpp",
    "expression.cpp", "term.cpp", "factor.cpp", "boolean.cpp",
    "unit.cpp", "io.cpp", "cpu.cpp", "amd64.cpp"]
)
    
line_run = environment.Program("line_run", ["line_run.cpp"], LIBS = [libtempest])