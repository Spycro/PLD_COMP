int getInt() {
    char x;
    int n = 0;

    // Wait for line break \n
    while((x = getchar()) != 10) {
        n = n * 10;
        n = n + (x - '0');
    }

    return n;
}

void printInt(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    
    if (x / 10) {
        printInt(x / 10);
    }

    putchar(x % 10 + '0');
}

void printWriteInt() {
    putchar('W');
    putchar('r');
    putchar('i');
    putchar('t');
    putchar('e');
    putchar(' ');
    putchar('a');
    putchar('n');
    putchar(' ');
    putchar('n');
    putchar('u');
    putchar('m');
    putchar('b');
    putchar('e');
    putchar('r');
    putchar(' ');
    putchar(':');
    putchar(' ');
}

void secretNumberRange(int min, int max) {
    putchar('T');
    putchar('h');
    putchar('e');
    putchar(' ');
    putchar('s');
    putchar('e');
    putchar('c');
    putchar('r');
    putchar('e');
    putchar('t');
    putchar(' ');
    putchar('n');
    putchar('u');
    putchar('m');
    putchar('b');
    putchar('e');
    putchar('r');
    putchar(' ');
    putchar('i');
    putchar('s');
    putchar(' ');
    putchar('i');
    putchar('n');
    putchar(' ');
    putchar('[');
    printInt(min);
    putchar(',');
    putchar(' ');
    printInt(max);
    putchar(']');
    putchar(10);
}

void secretNumberIs(int bigger) {
    putchar('T');
    putchar('h');
    putchar('e');
    putchar(' ');
    putchar('s');
    putchar('e');
    putchar('c');
    putchar('r');
    putchar('e');
    putchar('t');
    putchar(' ');
    putchar('n');
    putchar('u');
    putchar('m');
    putchar('b');
    putchar('e');
    putchar('r');
    putchar(' ');
    putchar('i');
    putchar('s');
    putchar(' ');
    if (bigger != 0) {
        putchar('b');
        putchar('i');
        putchar('g');
        putchar('g');
        putchar('e');
        putchar('r');
        putchar(' ');
        putchar('!');
    } else {
        putchar('l');
        putchar('o');
        putchar('w');
        putchar('e');
        putchar('r');
        putchar(' ');
        putchar('!');
    }
}

void printWin(int moves) {
    putchar('T');
    putchar('h');
    putchar('i');
    putchar('s');
    putchar(' ');
    putchar('i');
    putchar('s');
    putchar(' ');
    putchar('t');
    putchar('h');
    putchar('e');
    putchar(' ');
    putchar('s');
    putchar('e');
    putchar('c');
    putchar('r');
    putchar('e');
    putchar('t');
    putchar(' ');
    putchar('n');
    putchar('u');
    putchar('m');
    putchar('b');
    putchar('e');
    putchar('r');
    putchar(' ');
    putchar('!');
    putchar(10);
    putchar('Y');
    putchar('o');
    putchar('u');
    putchar(' ');
    putchar('f');
    putchar('o');
    putchar('u');
    putchar('n');
    putchar('d');
    putchar(' ');
    putchar('i');
    putchar('t');
    putchar(' ');
    putchar('i');
    putchar('n');
    putchar(' ');
    printInt(moves);
    putchar(' ');
    putchar('m');
    putchar('o');
    putchar('v');
    putchar('e');
    if (moves > 1) {
        putchar('s');
    }
    putchar(' ');
    putchar('!');
    putchar(10);
}

void printmany(int a, int b, int c, int d, int e, int f, int g, int h) {
    printInt(a);
    putchar(' ');
    printInt(b);
    putchar(' ');
    printInt(c);
    putchar(' ');
    printInt(d);
    putchar(' ');
    printInt(e);
    putchar(' ');
    printInt(f);
    putchar(' ');
    printInt(g);
    putchar(' ');
    printInt(h);
}

int main(){
    int secret = 127;
    int min = 0;
    int max = min + 1000;

    int moves = 0;
    int attempt = min-1;

    secretNumberRange(min, max);

    while (attempt != secret) {
        if (moves > 0) {
            if (secret > attempt) {
                secretNumberIs(1);
            } else {
                secretNumberIs(0);
            }
            putchar(10);
            putchar(10);
        }

        printWriteInt();
        attempt = getInt();
        moves++;
    }

    putchar(10);
    printWin(moves);

    return 0;
}
