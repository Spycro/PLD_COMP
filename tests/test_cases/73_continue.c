int main() {
	int a = 2;

    while(a<5){
        
        if(a==2){
            a = 10;
            continue;
        }
        ++a;
    }
    return a;
}