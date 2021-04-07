#include "ast/Scope.h"
#include <iostream>

#define WORDSIZE 8

std::shared_ptr<SymbolTableElement> Scope::getSymbol(std::string name){
    if(symbolicTable->symbolInTable(name)){
        return symbolicTable->getSymbol(name);
    }else if(parentScope == nullptr){
        return nullptr;
    }else{
        return parentScope->getSymbol(name);
    }
    
}

shared_ptr<SymbolTableElement> Scope::addTempVariable(const VarType::Type* variableType){
    int mem64 = getMemoryCounter64AndIncrement();
    return symbolicTable->addVariable(std::to_string(mem64), variableType, mem64);
}

void Scope::addVariable(std::string name,const VarType::Type *variableType)
{
    if(getSymbol(name)!= nullptr){
        std::cerr<<"name is already used in scope" <<std::endl;
    }
    symbolicTable->addVariable(name, variableType, getMemoryCounter64AndIncrement());
}

void Scope::addArray(std::string name, const VarType::Type *functionType, int size)
{
    if(getSymbol(name)!= nullptr){
        std::cerr<<"name is already used in scope" <<std::endl;
    }
    int baseMemoryCounter = getMemoryCounter64AndIncrement();
    int allocated = WORDSIZE;
    int needed = size * functionType->getSize();
    while (allocated < needed) {
        allocated += WORDSIZE;
        getMemoryCounter64AndIncrement();
    }
    symbolicTable->addArray(name, functionType, size, baseMemoryCounter);
}

void Scope::addFunction(std::string name, const VarType::Type *functionType)
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