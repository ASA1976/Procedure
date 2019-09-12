// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "procedure.hpp"

using namespace procedure;

// Link with test_extern.cpp (only)
void Invoke( const Procedural<void>& );

template <class Typical>
static inline auto Produce( Typical& object ) 
{
    return Procure( object, Guide<void> );
}

template <class Typical, class MethodLocative>
static inline auto Produce( Typical& object, MethodLocative method ) 
{
    return Procure( object, method, Guide<void> );
}

#include "test.conditions"
int main()
{
    static auto& Produce1 = Produce<Test1Typical>;
    static auto& Produce2 = Produce<Test2Typical>;
    static auto& Produce3 = Produce<Test3Typical>;
    static auto& Produce4 = Produce<Test4Typical, Test4Methodic>;
    RunTests( Invoke, Produce1, Produce2, Produce3, Produce4 );
}
