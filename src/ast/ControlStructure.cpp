#include "ast/ControlStructure.h"
#include <iostream>

using namespace std;

void ControlStructure::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"ControlStructure"<<endl;
}
