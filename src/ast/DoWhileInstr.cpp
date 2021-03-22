#include "ast/DoWhileInstr.h"
#include <iostream>

using namespace std;

void DoWhileInstr::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"DoWhileInstr"<<endl;
}
