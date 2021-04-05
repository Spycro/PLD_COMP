#include "SymbolTable.h"
#include <iostream>

using namespace std;

void SymbolTable::addVariable (string variableName, Type* variableType) {

    shared_ptr<SymbolTableElement> buffer = make_shared<SymbolTableElement>(variableType,false,false,false,0);
    bool test = elements->emplace(variableName,buffer).second;
    if(!test) {
        cerr<<"name is already used";
    }
}

void SymbolTable::addFunction (string functionName, Type* functionReturnType) {
    shared_ptr<SymbolTableElement> element = make_shared<SymbolTableElement>(functionReturnType, true);
    bool test = elements->emplace(functionName,element).second;
    if(!test) {
        cerr<<"name is already used";
    }

}