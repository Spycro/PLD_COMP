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

int f (int n) {
    if(n == 0 || n == 1) {
        return n;
    } else {
        return(f(n-1) + f(n-2));
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

    int c;
    int result = 0;

    for(c=0;c<=n;c++) {
        result = f(c);
        print(result);
        putchar(10);
    }

    return result;
}
