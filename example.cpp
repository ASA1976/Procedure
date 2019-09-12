// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
// #define PROCEDURE_MODULE_NOTHROW
#include "procedure.hpp"
#include <iostream>

using namespace std;
using namespace procedure;

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
    Demonstrate( Procure( Object, Guide<void> ) );
    Demonstrate( Procure( Object, &Class::member, Guide<void> ) );
    Demonstrate( Procure( Lambda, Guide<void> ) );
    Demonstrate( Procure( Function, Guide<void> ) ); // Matched
    Demonstrate( Procure( Function ) ); // Deduced
}
