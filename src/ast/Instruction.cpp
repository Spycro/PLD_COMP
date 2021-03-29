#include "ast/Instruction.h"
#include <iostream>

using namespace std;

void Instruction::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Instruction"<<endl;
}
