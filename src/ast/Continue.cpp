#include "ast/Continue.h"
#include <iostream>

using namespace std;

void Continue::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Continue"<<endl;
}
