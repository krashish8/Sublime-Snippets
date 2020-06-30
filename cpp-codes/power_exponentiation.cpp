int power(int x, int y) 
{ 
    int res = 1;
    x = x % MOD;
    while (y) {
    	if(y & 1) res = res * x % MOD;
    	y >>= 1;
        x = x * x % MOD;
    }
    return res; 
}
