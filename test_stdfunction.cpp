// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include <functional>

using namespace std;

// Link with test_extern.cpp (only)
void CallFunction( const function<void()>& );

template <class Typical>
static inline function<void()> Produce( Typical& object ) 
{
    return object;
}

template <class Typical, class MethodLocational>
static inline function<void()> Produce( Typical& object, MethodLocational method ) 
{
    return bind( method, object );
}

#define TEST_CALL CallFunction
#define TEST_PRODUCE1 Produce<Test1Typical>
#define TEST_PRODUCE2 Produce<Test2Typical>
#define TEST_PRODUCE3 Produce<Test3Typical>
#define TEST_PRODUCE4 Produce<Test4Typical, Test4Methodic>
#include "test.conditions"
