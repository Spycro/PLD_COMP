int main() {
	int a = 3;
	int b = 5;
	int c, d;
	d = 2 * (c = a + b);
	c = c - 1;
	a = b - a;
    return c * (d * a - 3) / 2;
}
