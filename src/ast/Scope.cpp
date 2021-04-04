#include "ast/Scope.h"

void Scope::addVariable(string name, Type *variableType)
{
    symbolicTable->addVariable(name, variableType);
}

void Scope::addFunction(string name, Type *functionType)
{
    symbolicTable->addFunction(name, functionType);
}

std::string Scope::toString()
{
    return "Scope";
}
