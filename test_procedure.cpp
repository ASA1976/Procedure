// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "test.conditions"
#include "procedure.hpp"

using namespace procedure;

// Link with test_extern.cpp
void Consume( const Procedural<void>& );

template <class Typical>
static inline auto Produce( Typical& object ) 
{return Procure( object, Guide<void> );}

template <class Typical, class MethodLocative>
static inline auto Produce( Typical& object, MethodLocative method ) 
{return Procure( object, method, Guide<void> );}

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
