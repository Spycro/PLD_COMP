int main() {
	char a;
	a='A';
	int i = 1;
	while(a<'Z'+1){
		if(i) {
			putchar(a);
			--i;
		}
		else{
			++i;
		}
		a=a+1;
	}
	return 0;
}