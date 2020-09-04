int multiply(int a, int b) {
    a = a % MOD;
    b = b % MOD;
    int res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % MOD;
        a = (2 * a) % MOD;
        b = b >> 1;
    }
    return res;
}
