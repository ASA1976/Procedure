// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
// #define PROCEDURE_MODULE_NOTHROW
// #define PROCEDURE_MODULE_NORTTI
// #define PROCEDURE_MODULE_NOSTDCPP
#include "procedure.hpp"
#include <iostream>

using namespace std;
using namespace procedure;

auto Lambda = [] {cout << "Lambda" << endl;};
void Function() {cout << "Function" << endl;}
const struct Class {
    void operator()() const {cout << "Functor" << endl;}
    void member() const {cout << "Member Function" << endl;}
} Object;

void CallProcedure( const Procedural< void >& call ) {call();}

const auto LambdaProcedure = Procure( Lambda, Guide< void > );
const auto FunctionProcedure = Procure( Function, Guide< void > );
const auto FunctorProcedure = Procure( Object, Guide< void > );
const auto MethodProcedure = Procure( Object, &Class::member, Guide< void > );

template <typename Resultant, typename ...Parametric>
class Conventional {
public:
    using SameConventional = Conventional< Resultant, Parametric... >;
    using SameProcedural = Procedural< Resultant, Parametric... >;
    constexpr Conventional( const SameProcedural& procedure ) : 
        procedure( &procedure ) {}
    constexpr Conventional( const SameConventional& copy ) : 
        procedure( copy.procedure ) {}
    constexpr operator const SameProcedural&() const 
    {
        return *procedure;
    }
    constexpr SameConventional& operator=( const SameConventional& copy )
    {
        procedure = copy.procedure;
        return *this;
    }
    constexpr bool operator==( const SameProcedural& procedure ) 
    {
        return *this->procedure == procedure;
    }
private:
    const SameProcedural* procedure;
};

template <size_t Length>
constexpr void ShuffleCalls( Conventional< void >(&calls)[Length] ) 
{
    if (Length < 2) return;
    Conventional< void > swap = calls[0];
    for (size_t index = 1; index < Length; index++)
        calls[index - 1] = calls[index];
    calls[Length - 1] = swap;
}

template <size_t Length>
constexpr void PerformCalls( Conventional< void >(&calls)[Length] ) 
{
    for (size_t index = 0; index < Length; index++)
        CallProcedure( calls[index] );
}

int main() 
{
    Conventional< void > calls[] = {
        LambdaProcedure, FunctionProcedure, FunctorProcedure, MethodProcedure
    };
    PerformCalls( calls );
    ShuffleCalls( calls );
    cout << endl;
    PerformCalls( calls );
    ShuffleCalls( calls );
    cout << endl;
    PerformCalls( calls );
    ShuffleCalls( calls );
    cout << endl;
    PerformCalls( calls );
    ShuffleCalls( calls );
    cout << endl;
    cout << "Run-time type information (RTTI) is: ";
    if (calls[0] == Procure( Lambda, Guide< void > ))
        cout << "working perfectly";
    else
        cout << "not available";
    cout << endl;
    return
        calls[0] == LambdaProcedure &&
        calls[1] == FunctionProcedure &&
        calls[2] == FunctorProcedure &&
        calls[3] == MethodProcedure
        ? 0 : -1;
}
