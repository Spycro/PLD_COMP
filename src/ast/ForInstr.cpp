#include "ast/ForInstr.h"
#include <iostream>

using namespace std;

void ForInstr::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"ForInstr"<<endl;
}
