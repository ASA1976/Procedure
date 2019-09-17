// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include <functional>

using namespace std;
using TestFunctional = function< void() >;

// Link with test_extern.cpp (only)
void CallFunction( const TestFunctional& );

template <class Typical>
static inline TestFunctional Produce( Typical& object ) 
{
    return object;
}

template <class Typical, class MethodLocational>
static inline TestFunctional Produce( Typical& object, MethodLocational method ) 
{
    return bind( method, object );
}

#define TEST_CALL CallFunction
#define TEST_PRODUCE1 Produce<Test1Typical>
#define TEST_PRODUCE2 Produce<Test2Typical>
#define TEST_PRODUCE3 Produce<Test3Typical>
#define TEST_PRODUCE4 Produce<Test4Typical, Test4Methodic>
#include "test.conditions"
