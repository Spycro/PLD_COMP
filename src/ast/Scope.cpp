#include "ast/Scope.h"

void Scope::addVariable(std::string name, Type *variableType)
{
    symbolicTable->addVariable(name, variableType);
}

void Scope::addFunction(std::string name, Type *functionType)
{
    symbolicTable->addFunction(name, functionType);
}

std::string Scope::toString()
{
    return "Scope";
}
