int main(){
    int x = 5;
    int y = 6;
    int a = 0;

    if(x == y){
        a = 1;
    }
    else{
        a = 2;
    }

    if(x < y){
        a = a + 2;
    }
    else{
        a = a + 3;
    }

    return a;
}