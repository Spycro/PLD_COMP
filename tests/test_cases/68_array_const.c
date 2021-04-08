int main() {
	int a = 1;

    int i[3];

    i[0] = a;
    i[a] = 4;
    a = i[1];
    return a;
}