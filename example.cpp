// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#define FUNCTION_HEADER "function" // <function>
#include FUNCTION_HEADER
#include <cstdio>

using namespace function;
using Demonstrative = const Procedural< void, const char* >;

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

void Demonstrate( Demonstrative& invoke, const char* message ) 
{
    invoke( message );
}

int main() 
{
    static const auto& Type = Deduction< void, const char* >;
    static const auto& Member = &Class::member;
    Demonstrate( Designate( Object, Type ), "Functor" );
    Demonstrate( Designate( Object, Member, Type ), "Member Function" );
    Demonstrate( Designate( Lambda, Type ), "Lambda" );
    Demonstrate( Designate( Function ), "Function" );
}
