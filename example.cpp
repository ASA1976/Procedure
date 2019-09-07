// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#define FUNCTION_HEADER "function" // <function>
#include FUNCTION_HEADER // VS IDE Workaround
#include <iostream>

using namespace std;
using namespace function;

const struct Class {

    void operator()() const {cout << "Functor" << endl;}

    void member() const {cout << "Member Function" << endl;}

} Object;

auto Lambda = [] {cout << "Lambda" << endl;};

void Function() {cout << "Function" << endl;}

void Demonstrate( const Procedural<void>& invoke ) 
{ 
    invoke(); 
}

int main() 
{
    Demonstrate( Designate( Object, Deduction<void> ) );
    Demonstrate( Designate( Object, &Class::member, Deduction<void> ) );
    Demonstrate( Designate( Lambda, Deduction<void> ) );
    Demonstrate( Designate( Function ) );
}
