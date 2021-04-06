#include "ast/Scope.h"
#include <iostream>

std::shared_ptr<SymbolTableElement> Scope::getSymbol(std::string name){
    std::shared_ptr<SymbolTableElement> el;
    if(symbolicTable->symbolInTable(name)){
        return symbolicTable->getSymbol(name);
    }else if(parentScope == nullptr){
        return nullptr;
    }else{
        return parentScope->getSymbol(name);
    }
    
}

shared_ptr<SymbolTableElement> Scope::addTempVariable(VarType::Type* variableType){
    int mem64 = getMemoryCounter64AndIncrement();
    return symbolicTable->addVariable(std::to_string(mem64), variableType, mem64);
}

void Scope::addVariable(std::string name, VarType::Type *variableType)
{
    if(getSymbol(name)!= nullptr){
        std::cerr<<"name is already used in scope" <<std::endl;
    }
    symbolicTable->addVariable(name, variableType, getMemoryCounter64AndIncrement());
}

void Scope::addFunction(std::string name, VarType::Type *functionType)
{
    symbolicTable->addFunction(name, functionType, 0);
}

int Scope::getMemoryCounter64(){
    if(parentScope != nullptr){
      return parentScope->getMemoryCounter64();
    }
    return memoryCounter64;
}

std::string Scope::toString()
{
    return "Scope";
}

int Scope::getMemoryCounter64AndIncrement(){
    if(parentScope != nullptr){
        return parentScope->getMemoryCounter64AndIncrement();
    }
    memoryCounter64 += 8;
    return memoryCounter64;
}