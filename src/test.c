int main() {
    int a;
    int b;
    int c;
    a = 5;
    b = a;
    {
    c = a + b;
    }

    b=a;
    
    return c;
}