// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
// #define PROCEDURE_MODULE_NOTHROW
// #define PROCEDURE_MODULE_NORTTI
// #define PROCEDURE_MODULE_NOSTDCPP
#include "procedure.hpp"
#include <iostream>

using namespace std;
using namespace procedure;
using Abstract = const Procedural<void>&;

struct Class {
    void operator()() const { cout << "Functor Object" << endl; }
    void nonstatic_member() const { cout << "Object Member Function" << endl; }
    static void static_member() { cout << "Class Member Function" << endl; }
};

void Function()
{
    cout << "Function Object" << endl;
}

void Demonstrate(Abstract call)
{
    call();
}

int main()
{
    auto lambda = [] { cout << "Lambda Expression" << endl; };
    const Class object;
    Demonstrate(Procure(object, Guide<void>));
    Demonstrate(Procure(object, &Class::nonstatic_member, Guide<void>));
    Demonstrate(Procure(Class::static_member));
    Demonstrate(Procure(Function));
    Demonstrate(Procure(lambda, Guide<void>));
}
