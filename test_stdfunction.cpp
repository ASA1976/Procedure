// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "test.conditions"
#include <functional>

using namespace std;

// Link with test_extern.cpp
void Consume( const function<void()>& );

template <typename Typical>
static inline function<void()> Produce( Typical& object ) 
{return object;}

template <class Typical, class MethodLocative>
static inline function<void()> Produce( Typical& object, MethodLocative method ) 
{return bind( method, object );}

static inline void RunAllTests() 
{
    RunTest1( Consume, Produce<Test1Typical> );
    RunTest2( Consume, Produce<Test2Typical> );
    RunTest3( Consume, Produce<Test3Typical> );
    RunTest4( Consume, Produce<Test4Typical, Test4Methodic> );
}

int main()
{
    for (size_t count = 0; count < LoopCount; count++)
        RunAllTests();
}
