// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "procedure.hpp"
#include <functional>

using TestProcedural = procedure::Procedural<void>;
using TestFunctional = std::function<void()>;

void Invoke( const TestProcedural& invoke ) 
{
    invoke();
}

void Invoke( const TestFunctional& invoke ) 
{
    invoke();
}
