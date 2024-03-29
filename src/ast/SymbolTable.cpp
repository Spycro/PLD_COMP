#include "SymbolTable.h"
#include <iostream>

using namespace std;

shared_ptr<SymbolTableElement> SymbolTable::addVariable (string variableName, const VarType::Type* variableType, int mem64) {

    shared_ptr<SymbolTableElement> buffer = make_shared<SymbolTableElement>(variableType,false,false,false,mem64);
    elements->emplace(variableName, buffer);
    return buffer;
}

shared_ptr<SymbolTableElement> SymbolTable::addArray(string variableName, const VarType::Type* variableType, int size, int mem64) {

    shared_ptr<SymbolTableElement> buffer = make_shared<SymbolTableElement>(variableType,false,false,false,mem64);
    elements->emplace(variableName, buffer);
    return buffer;
}

shared_ptr<SymbolTableElement> SymbolTable::addFunction (string functionName, const VarType::Type* functionReturnType, int mem64) {
    shared_ptr<SymbolTableElement> element = make_shared<SymbolTableElement>(functionReturnType, false, false, true, mem64);
    elements->emplace(functionName, element);
    return element;
}