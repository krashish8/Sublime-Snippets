int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
}

int ncr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
}
