
# Procedure

© 2019 Aaron Sami Abassi
Licensed under the Academic Free License version 3.0

## What is the 'procedure' template library?

* A universal C++ procedure call system for application programming
* Procedures include functions, member functions, lambdas and operator overloads
* The library is entirely contained in the source code header [**procedure.hpp**](https://github.com/ASA1976/Procedure/blob/master/procedure.hpp#L1)

## What does it do?

Given matching return type, parameter types and calling convention:

* Call procedures using a pure abstract Procedural class
* Compare or call procedures using a pure abstract ComparablyProcedural class

## Who should use it?

* Suitable for high performance computing, gaming and application development
* **Can be used on any platform** with the use of header macros in certain cases
* Arduino/micro-controller users be sure to read; **Is this template library portable?**

## How is it used?

* Reference or pointer to constant Procedural can be used to call an object
* As above to constant ComparablyProcedural can be used to compare call objects
* The Guide template is required for return and parameter type deductions
* Use Procure and ProcureComparably templates to initialize Procedural objects
* Objective classes represent function, lambda or call operator overload calls
* Methodic classes represent object member function calls
* SimplyObjective and SimplyMethodic derive from Procedural only
* ComparablyObjective and ComparablyMethodic derive from ComparablyProcedural
* [Simple example](https://github.com/ASA1976/Procedure/blob/master/example.cpp#L1) which demonstrates basic use for each type of procedure
* [Complex example](https://github.com/ASA1976/Procedure/blob/master/erasure.cpp#L1) which demonstrates comparison and a copy convention class

## Why Procedural and ComparableProcedural class templates?

* If comparison is not required, using ComparablyProcedural is not recommended
* Performance may be *slightly* hindered using the larger comparable classes
* See discrepency in [test_procedure](https://github.com/ASA1976/Procedure/blob/master/procedure_results.txt#L1) times with [test_comparable](https://github.com/ASA1976/Procedure/blob/master/comparable_results.txt#L1) times

## Is this template library portable?

* This library is designed to work on any C++14 compliant compiler platform
* PROCEDURE_MODULE_NOSTDCPP prevents the use of type_traits based verifications
* PROCEDURE_MODULE_NOTHROW prevents **this** library from throwing exceptions
* PROCEDURE_MODULE_NORTTI read below; **What about operation without RTTI?** 

## What about operation without RTTI?

* The following only applies to the equal to operator from ComparablyProcedural
* Comparison with RTTI will compare the callable object addresses for equality
* **Comparison without RTTI relies instead on Procedural object uniqueness**
* If RTTI is not available, the following semantics must always be respected
* Limit of one Procedural object per unique callable object address
* For member functions, unique object address and member pointer combinations
* This library **will not enforce** Procedural uniqueness with or without RTTI

## What if the ability to copy the procedural interface object is required?

* Copy constructors are available on each specific Objective and Methodic type
* However type erasure only extends to the Procedural base classes
* See the use of the **Conventional** type template in the [complex example](https://github.com/ASA1976/Procedure/blob/master/erasure.cpp#L1)
* If the above is not suitable, please see [invocation](https://github.com/ASA1976/RAP-BTL/blob/master/invocation.cpp#L1) in the [RAP-BTL](https://github.com/ASA1976/RAP-BTL)

### How to contact the author?

I can be contacted [here](mailto:rap.paradigm@gmail.com?subject=procedure.hpp).

