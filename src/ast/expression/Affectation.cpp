#include "ast/expression/Affectation.h"
#include <iostream>

using namespace std;

void Affectation::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Affectation"<<endl;
}

