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

const auto LambdaProcedure = ProcureComparably( Lambda, Guide< void > );
const auto FunctionProcedure = ProcureComparably( Function, Guide< void > );
const auto FunctorProcedure = ProcureComparably( Object, Guide< void > );
const auto MethodProcedure = ProcureComparably( Object, &Class::member, Guide< void > );

template <typename Resultant, typename ...Parametric>
class Conventional {
public:
    using BaseProcedural = Procedural< Resultant, Parametric... >;
    using SameProcedural = ComparablyProcedural< Resultant, Parametric... >;
    using SameConventional = Conventional< Resultant, Parametric... >;
    constexpr Conventional( const SameProcedural& procedure ) : 
        procedure( &procedure ) {}
    constexpr Conventional( const SameConventional& copy ) : 
        procedure( copy.procedure ) {}
    constexpr operator const SameProcedural&() const 
    {
        return *procedure;
    }
    constexpr bool operator==( const BaseProcedural& relative ) const
    {
        return *procedure == relative;
    }
    constexpr SameConventional& operator=( const SameProcedural& procedure )
    {
        this->procedure = &procedure;
        return *this;
    }
private:
    const SameProcedural* procedure;
};

void CallProcedure( const Procedural< void >& call ) 
{
    call();
}

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
    cout << "Run-time type information (RTTI): ";
    if (calls[0] == Procure( Lambda, Guide< void > ))
        cout << "is enabled";
    else
        cout << "is disabled";
    cout << endl;
}
