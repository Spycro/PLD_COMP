void print(int x)
{
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    
    if (x / 10) {
        print(x / 10);
    }

    putchar(x % 10 + '0');
}

int factoriel (int n){
    if(n == 0) {
        return 1;
    } else {
        return (n * factoriel(n-1));
    }
}

int main() {

    putchar('n');
    putchar(' ');
    putchar('?');
    putchar(10); // line break \n

    char x;
    int n = 0;

    // Wait for line break \n
    while((x = getchar()) != 10) {
        n = n * 10;
        n = n + (x - '0');
    }

    print(factoriel(n));
    putchar(10);

    return 0;
}