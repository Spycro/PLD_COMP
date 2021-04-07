int main(){
    int x = 5;
    int y = 6;
    int a = 0;

    if(x == y){
        a = 1;
    }
    else if (x > y){
        a = 2;
    }
    else {
        a = 3;
    }

    if(x == y){
        a = a + 1;
    }
    else if (x < y){
        a = a + 2;
    }
    else {
        a = a + 3;
    }

    a++;

    return a;
}