// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "test.conditions"
#include <functional>

using namespace std;

// Link with test_extern.cpp (only)
void Consume( const function<void()>& );

template <typename Typical>
static inline function<void()> Produce( Typical& object ) 
{return object;}

template <class Typical, class MethodLocative>
static inline function<void()> Produce( Typical& object, MethodLocative method ) 
{return bind( method, object );}

int main()
{
    static auto& Produce1 = Produce<Test1Typical>;
    static auto& Produce2 = Produce<Test2Typical>;
    static auto& Produce3 = Produce<Test3Typical>;
    static auto& Produce4 = Produce<Test4Typical, Test4Methodic>;
    for (size_t count = 0; count < LoopCount; count++)
        RunAllTests( Consume, Produce1, Produce2, Produce3, Produce4 );
}
