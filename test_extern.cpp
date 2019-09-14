// � 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "procedure.hpp"
#include <functional>

using TestProcedural = procedure::Procedural<void>;
using TestFunctional = std::function<void()>;

void CallProcedure( const TestProcedural& invoke ) 
{
    invoke();
}

void CallFunction( const TestFunctional& invoke ) 
{
    invoke();
}
