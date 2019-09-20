# Procedure
#### Universal C++ stored procedure call interface for application programming

© 2019 Aaron Sami Abassi

Licensed under the Academic Free License version 3.0

## Introduction

This ISO C++ 2014 standard compliant 
[template header](https://github.com/ASA1976/Procedure/blob/master/procedure.hpp#L1)
provides class templates and function templates which allow a system to call any
kind of C++ stored procedure with matching call return and parameter 
types.  This call system is intended for application development audiences 
primarily, including high performance computing applications.  It is **not 
intended for embedded** and certain real-time systems programming audiences, 
please see 
[invocation](https://github.com/ASA1976/RAP-BTL/blob/master/invocation.hpp#L1) 
in the
[Relational Association Programming Basic Template Library for C++](https://github.com/ASA1976/RAP-BTL) 
if stringent memory space or trivial copying of call site wrapper objects are 
required, with similar performance levels.

## Usage

The header is named 'procedure.hpp'and can either be copied into a source 
project tree or installed as a standard system header file.  The file strictly 
contains one name space with templates which are unused unless their scope is 
referenced after their inclusion.

In order to call any stored procedure, one uses a template instance of the
Procedural type template in the 'procedure' name space to specify the return 
type and parameter types for the call.  Constant references to such base class 
objects can be used to invoke the virtual call operator which is implemented by
the derived class.

In order to specify a function, lambda, object call operator or object member 
function call, one invokes one the overloaded Procure function templates in 
the 'procedure' name space.  To specify a function, one invokes the Procure
overload with a function reference parameter (1).  To specify a call operator 
overload or lambda, one invokes the Procure overload with an object reference 
and null function pointer parameters (2).  To specify an object member function 
call, one uses the Procure overload with an object reference, constant pointer 
to member and null function pointer parameters (3).

In order to deduce the return and parameter types for call operator overloads,
lambdas and object member function calls, the Guide variable template provides a
null pointer to function constant expression, which is provided to the 
corresponding Procure function templates.

## Example

Please see the 
[example](https://github.com/ASA1976/Procedure/blob/master/example.cpp#L1)
which demonstrates each use case for a simple void return type and constant
character pointer parameter type (1).

## Standardization Statement

NB: International Organization for Standardization, Working Group 21 (WG21)

Under the terms of the
[Academic Free License version 3.0](https://opensource.org/licenses/AFL-3.0)
, please feel free to incorporate these templates in the standard library 
in any modified form pursuant to the AFL license terms.

