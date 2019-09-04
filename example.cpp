// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#define FUNCTION_HEADER "function" // <function>
#include FUNCTION_HEADER
#include <iostream>
#include <string>

using namespace std;
using namespace function;
using Demonstrative = const Procedural< void, const string& >;

const struct Class {

    void operator()( const string& message ) const {cout << message << endl;}

    void member( const string& message ) const {cout << message << endl;}

} Object;

auto Lambda = []( const string& message ) {cout << message << endl;};

void Function( const string& message ) {cout << message << endl;}

void Demonstrate( Demonstrative& invoke, const string& message ) 
{ 
    invoke( message ); 
}

int main() 
{
    static const auto& Type = Deduction< void, const string& >;
    static const auto& Member = &Class::member; // &decltype(Object)::member
    Demonstrate( Designate( Object, Type ), "Functor" );
    Demonstrate( Designate( Object, Member, Type ), "Member Function" );
    Demonstrate( Designate( Lambda, Type ), "Lambda" );
    Demonstrate( Designate( Function ), "Function" );
}
