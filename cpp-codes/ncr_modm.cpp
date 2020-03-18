int power(int x, int y) 
{ 
    int res = 1;
    x = x%MOD;
    while(y!=0) {
    	if(y&1)
    		res = (res*x)%MOD;
    	y = y>>1;
    	x = (x*x)%MOD;
    }
    return res; 
}

int modInverse(int n)
{
	return power(n, MOD-2);
}

int ncr(int n, int r, int p) 
{ 
	if (r==0) 
		return 1; 
	int fac[n+1]; 
	fac[0] = 1; 
	for (int i=1 ; i<=n; i++) 
		fac[i] = fac[i-1]*i%MOD; 
	return (fac[n]* modInverse(fac[r]) % MOD * modInverse(fac[n-r]) % MOD) % MOD; 
}
