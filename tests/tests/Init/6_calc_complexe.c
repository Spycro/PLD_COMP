int main() {
	int a = 3;
	int b = 5;
	int c, d;
	d = 2 * (c = a + b);
	c = c - 1;
	a = b - a;
    return c * (d * a - 3) / 2;
    // = ((3 + 5) - 1) * ((2 * (3 + 5)) * (5 - 3) - 3)
    // = 7 * (16 * 2 - 3) = 203
}
