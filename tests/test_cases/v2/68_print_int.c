void print(int x)
{
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    
    if (x / 10) {
        print(x / 10);
    }

    putchar(x % 10);

    putchar(x % 10 + '0');
}

int main() {
    
    print(528);

    return 0;
}