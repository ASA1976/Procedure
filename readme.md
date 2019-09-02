# Function
#### Universal C++ stored procedure call interface for application programming

© 2019 Aaron Sami Abassi

Licensed under the Academic Free License version 3.0

## Introduction

This template header provides class templates and function templates, which
allow a programmer to call any C++ invocation object with matching call return 
and parameter types.  This implementation is intended for application 
development audiences primarily, including high performance computing 
applications.  It is **not** intended for embedded and certain real-time systems
programming audiences, please see 
[invocation](https://github.com/ASA1976/RAP-BTL/blob/master/invocation.hpp) 
in the
[Relational Association Programming Basic Template Library for C++](https://github.com/ASA1976/RAP-BTL) 
if a much more compact data area is desired with similar performance levels.
This header file conforms to the ISO C++ 2014 language standard specification.

## Usage

The header is named 'function' and can either be included in a source project
tree or installed as a standard header file on the system.  The header file 
strictly contains one name space containing templates which are unused unless
their scope is referenced after their inclusion.

In order to call any stored procedure, one uses a template instance of the
Procedural type template in the 'function' name space to specify the return type 
and parameter types for the call.  Constant references to such base class 
objects are used to invoke the virtual call operator which is implemented by the 
designated derived class.

In order to designate a function, lambda, object call operator or object member 
function call, one invokes one the overloaded Designate function templates in 
the 'function' name space.  To designate a function, one uses the overload with
a function reference parameter (1).  To designate an object call operator or 
lambda, one uses the overload with an object reference and null function pointer 
reference parameters (2).  To designate an object member function call, one uses 
the overload with an object reference, constant pointer to member reference and
null function pointer reference parameters (3).

In order to deduce the return and parameter types for object call operator,
lambda and object member function calls, the Deduction variable template 
provides a null pointer to function constant expression which is provided to the
Designate function template.

## Example

Please see the 
[example](https://github.com/ASA1976/Function/blob/master/example.cpp#L1)
which demonstrates each use case for a simple void return type and constant
character pointer parameter type (1).

## Standardization Statement

NB: International Organization for Standardization, Working Group 21 (WG21)

Under the terms of the
[Academic Free License version 3.0](https://opensource.org/licenses/AFL-3.0)
, please feel free to incorporate these templates in the standard library 
in any modified form pursuant to the AFL license terms.

