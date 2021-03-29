#include "ast/WhileInstr.h"
#include <iostream>

using namespace std;

void WhileInstr::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"WhileInstr"<<endl;
}
