int fac[N];

int power(int x, int y) {
    int res = 1;
    x = x % MOD;
    while (y != 0) {
        if (y & 1) res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}

int ncr(int n, int r) {
    if (n < r) return 0;
    return fac[n] * power(fac[r], MOD - 2) % MOD * power(fac[n - r], MOD - 2) % MOD;
}

	fac[0] = 1;
    for (int i = 1; i < N; i++)
        fac[i] = fac[i-1] * i % MOD;
