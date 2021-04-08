int main() {

	char a = 'A';
	int i = 1;

	while(a < 'Z'+1) {

		if(i % 2) {
			putchar(a);
		} else {
			putchar('-');
		}

		a = a + 1;
        ++i;
	}

    putchar(10); // \n

	return 0;
}