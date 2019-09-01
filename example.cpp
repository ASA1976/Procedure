// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include "function"
#include <cstdio>

using namespace function;
using Invocative = const Procedural< void, const char* >;

const struct Class {

    void operator()( const char* message ) const 
    {
        puts( message );
    }

    void member( const char* message ) const 
    {
        puts( message );
    }

} Object;

auto Lambda = []( const char* message ) 
{
    puts( message );
};

void Function( const char* message ) 
{
    puts( message );
}

void Demonstrate( Invocative& invoke, const char* message ) 
{
    invoke( message );
}

int main() 
{
    constexpr auto& Type = Deduction< void, const char* >;
    Demonstrate( Designate( Object, Type ), "Functor" );
    Demonstrate( Designate( Object, &Class::member, Type ), "Member Function" );
    Demonstrate( Designate( Lambda, Type ), "Lambda" );
    Demonstrate( Designate( Function ), "Function" );
}
