int main() {
	int a, b = 0;
	a = 4;
	--a;
	a = a--;
	a = a + -(++b);
    return a--;
}
