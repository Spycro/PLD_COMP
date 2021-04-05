#include "SymbolTable.h"
#include <iostream>

using namespace std;

void SymbolTable::addVariable (string variableName, VarType::Type* variableType) {

    shared_ptr<symbolTableElement> buffer = make_shared<symbolTableElement>(variableType,false,false,false,0);
    bool test = elements->emplace(variableName,buffer).second;
    if(!test) {
        cerr<<"name is already used";
    }
}

void SymbolTable::addFunction (string functionName, VarType::Type* functionReturnType) {
    shared_ptr<symbolTableElement> element = make_shared<symbolTableElement>(functionReturnType, true);
    bool test = elements->emplace(functionName,element).second;
    if(!test) {
        cerr<<"name is already used";
    }

}