int factoriel (int n){
    if(n == 0) {
        return 1;
    } else {
        return (n * factoriel(n-1));
    }
}

int main () {
    int f = factoriel(4);
    return f;
}