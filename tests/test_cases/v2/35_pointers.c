int main() {
    int a ;
    int *b = &a;
    *b = 2;
    int res = *b;
    return res;
} 