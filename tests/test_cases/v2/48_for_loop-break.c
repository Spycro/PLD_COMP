int main() {
	int a = 0;

    for(int i = 0 ; i < 5 ; ++i){
        if(a >= 3) break;

        a = a + i;
    }

    return a;
}