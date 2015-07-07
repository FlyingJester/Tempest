Tempest Compiler
================

Tempest is a compiler for an experimental language called "Pluto". It is a work in progress, but has several fully functional features:
 * Function Declarations
 * Variable Declarations and Initializers
 * Expression Parsing
 * Scoping Rules
 * Sized Integers
 * Arrays (called Scalars)
 * Structured Data (called Complexes)

Features still unimplemented:
 * Function Arguments
 * Function Calls
 * Vector Operations
 * Name Complex Fields
 * Floating Point Operations

Pluto Language Description
--------------------------

The Pluto language is a fairly simple structured language. It supports three data types: Integrals, Scalars and Complexes.
An Integral is a sized integer. The size must be a power of two, and the maximum size is guaranteed to be at least 64-bit.
Scalars are arrays of homogenously sized data. Scalars of integrals and floating point numbers support vector arithmetic notation.
Complexes are structures of data. A complex is simply a pair of data, which can be of any type. Complex structures are formed of trees
of complexes.

Pluto has some functional aspects. A function in a more traditional sense is called a "subroutine". Subroutines cannot be called
recursively, and cannot be declared in a nested manner.
A second type of function called a "nanoroutine" is supported. Nanoroutines can only be declared nested within subroutines, and
can only be called from within their own subroutine. A nanoroutine is more like a coroutine, and calls to nanoroutines do not grow the
stack. All nested calls to nanoroutines share the same argument variables.

Pluto has only two control structures, the nanoroutine and a branch statement. All loops are performed using branches and nanoroutine
calls. 

Types
-----

Examples of each:

```
% A forked binary tree:
%
%       X
%      / \
%     /\  \
%    /  \  \
%   /   /\  \
%  /\  3  4 /\
% 1  2        5
%
    {{ {1, 2}, {3, 4} }, { {}, 5 } }
% Array with the first seven fibonacci numbers. Note that it is prefixed with its size, similar to an integer.
    7[ 1, 1, 2, 3, 5, 8, 13 ]
% A four-byte integer representing 42:
    4(42)
% A native-sized integer can be represented simply as a number literal:
    42
% This is synonymous with:
    #(42)


% This is a planned feature. Don't look at it yet :)
% Automatic array sizing:
%    #[1, 2, 3]
```

A list can hold any data type, in a heterogenous manner. For instance:
```
    { 4[1, 2, 3, 4], 5} % Valid
    { 1, { {5, {} }, 3[2, 3, 4]} } % Valid
```
The first list holds a four-integer array on one node and the integer 5 on the other.
The second holds a complex mixture of integers, arrays, and other lists.

Consequently, any list that is syntactically valid is also a valid list construction.

However, arrays can only consist of one type of object. For instance:
```
    4[1, 2, 3, 4] % Valid
    3[3[1, 2, 3], 2[4, 5], 1[6]] % Valid, all elements are an array.
    2[3[1, 2, 3], 2[{}, {4, 5}]] % Valid. It doesn't matter that the second nested array holds a list, just both the elements in the main array are arrays.
    3[{}, {1, 2}, {2[3, 4], {}}] % Valid, a tree is always of the same type.
    
    2[[1], 2] % Invalid.
    2[{}, []] % Invalid.
    3[{}, 1, [2, 3]] % Very invalid. Where did you learn to fly?
```
This limitation also applies with different integer sizes.
```
    3[1, 2, 3] % Valid
    3[4(1), 4(2), 4(3)] % Valid
    
    2[2(1), 4(2)] % Invalid
    3[1, 4(2), 4(3)] % Invalid
    2[4(1), 2] % Invalid. Even if the native integer size is 4, the automatic size is still unique.
```

Type Notation
-------------

It is necessary to note type when defining functions (for parameter and return types) or variables. Types are noted in 
Nightmare similarly to how literals are written. The syntax is slightly different for integers compared to lists and arrays.

An integer type notation is its size followed by empty parantheses:
```
% A 4-byte integer type:
4()
% The native integer type:
#()
```

lists and arrays are noted somewhat differently:

```
% Universal list note. Any list is of this type.
{}

% Explictly empty list. This is only valid in type declarations.
{#}

% Lists can be qualified.
% A list that has a 2-byte integer as the first node and another list as the second.
% Note that the second list may or may not be empty.
{2(), {}}

% An array is noted by how many elements it will have and then the type, similar in some ways to an integer type.
% This notes an array of five each four-byte integers.
5[4()]
% An array of six lists
6[{}]

% List elements can be named, but this is currently not really useful except for argument names.
% A and B are both 8-byte integers.
{A:8(), B:8()}
% A is an array of 4 each 2-byte integers. B is an array of 8 lists.
{A:4[2()], B:8[{}]}
```

The notation of an explicitly empty list is mostly to keep its notation inside other lists and inside arrays consistent with how
arrays and integers are noted.

Small Example Programs
----------------------

```
test_module:
    subroutine 4() three:
        assigned return:3;
    .
.
```
Since Pluto is ignores whitespace, the same program can be written fairly succinctly. 

```
test_module:subroutine 4() three:assigned return:3;..
```

BNF Description of Tempest
--------------------------

This is primarily useful for language devs, but it may be useful to others as well.

```
<tempest_program> ::= <identifier> ':' <subroutine>+ '.'
<subroutine> ::= "subroutine" <type> <identifier> <variable>+ ':' [<variable> | <declaration> | <assignment> | <nanoroutine> ]* .
<nanoroutine> ::= "nanoroutine" <type> <identifier> <variable>+ ':' [<variable> | <declaration> | <assignment> ]* .

<value> ::= <integral_value> | <scalar_value> | <complex_value>

<expression> ::= ['-'] <term> [ <add_op> <term> ]*
<add_op> ::= '-' | '+'
<term> ::= <factor> [ <mult_op> <factor> ]*
<mult_op> ::= '/' | '*' | '%'
<factor> ::= <number> | <variable> | <call> | <access> | '(' <expression> ')'

<number> ::= <hexadecimal_literal> | <decimal_literal> | <octal_literal>
<size> ::= <number> | '#'

<integral_value> ::= <size> '(' <expression> ')'
<scalar_value> ::= <size> '[' [<expression> [, <expression> ] ] ']'
<complex_value> ::= '{' <value>, <expression> '}'

<type> ::= <integral_type> | <scalar_type> | <complex_type>
<integral_type> ::= <size> '(' ')'
<scalar_type> ::= <size> '[' <type> ']'
<complex_type> ::= '{' <type> '}'

<variable_decl> ::= "unassigned" <variable> ';'
<variable> ::= <identifier> ':' <type>

<declaration_decl> ::= "assigned" <declaration> ';'
<declaration> ::= <identifier> ':' <expression>

<assignment> ::= <identifier> '=' <expression> ';'

<identifier> ::= <'a'-'z' | 'A'-'Z'> [ <'a'-'z' | 'A'-'Z' | '1'-'9' | '0' | '_' ]*

<call> ::= <identifier> '(' [ <expression> [, <expression> ]* ] ')'
<access> ::= <identifier> '[' <expression> ']'
```


