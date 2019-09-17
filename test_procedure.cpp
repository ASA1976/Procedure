// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "procedure.hpp"

using namespace procedure;

// Link with test_extern.cpp (only)
void CallProcedure( const Procedural< void >& );

template <class Typical>
static inline auto Produce( Typical& object ) 
{
    return Procure( object, Guide< void > );
}

template <class Typical, class MethodLocational>
static inline auto Produce( Typical& object, MethodLocational method ) 
{
    return Procure( object, method, Guide< void > );
}

#define TEST_CALL CallProcedure
#define TEST_PRODUCE1 Produce<Test1Typical>
#define TEST_PRODUCE2 Produce<Test2Typical>
#define TEST_PRODUCE3 Produce<Test3Typical>
#define TEST_PRODUCE4 Produce<Test4Typical, Test4Methodic>
#include "test.conditions"
