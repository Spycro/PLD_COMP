int f (int n) {
    if(n == 0 || n == 1) {
        return n;
    } else {
        return(f(n-1) + f(n-2));
    }
}

int main() {
    putchar('n');
    putchar(':');
    putchar('[');
    putchar('1');
    putchar('-');
    putchar('9');
    putchar(']');
    putchar('?');

    char a = getchar();
    int n = a - 48;
    int i = 0;
    int c;
    int result;

    for(c=1;c<=n;c++) {
        result = f(i);
        i++;
    }

    return result;
}
