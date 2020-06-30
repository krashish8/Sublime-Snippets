bool isPrimeFermat(int n, int iter = 5) {
    if (n < 4) return n == 2 || n == 3;
    for (int i = 0; i < iter; i++) {
        int a = 2 + rand(0, n - 3);
        if (power(a, n - 1) != 1)
            return false;
    }
    return true;
}
