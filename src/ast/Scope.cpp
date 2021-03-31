#include "ast/Scope.h"
#include <iostream>

using namespace std;

void Scope::addVariable(string name, Type* variableType) {
    symbolicTable->addVariable(name,variableType);
}

void Scope::addFunction(string name, Type* functionType) {
    symbolicTable->addFunction(name,functionType);
}


void Scope::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Scope"<<endl;
}
