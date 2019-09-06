// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#define FUNCTION_HEADER "function" // <function>
#include FUNCTION_HEADER
#include <iostream>

using namespace std;
using namespace function;

const struct Class {

    void operator()() const {cout << "Functor" << endl;}

    void member() const {cout << "Member Function" << endl;}

} Object;

auto Lambda = [] {cout << "Lambda" << endl;};

void Function() {cout << "Function" << endl;}

void Demonstrate( const Procedural< void >& invoke ) 
{ 
    invoke(); 
}

int main() 
{
    static const auto& Type = Deduction< void >;
    Demonstrate( Designate( Object, Type ) );
    Demonstrate( Designate( Object, &Class::member, Type ) );
    Demonstrate( Designate( Lambda, Type ) );
    Demonstrate( Designate( Function ) );
}
