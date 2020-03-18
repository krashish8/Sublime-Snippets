bool prime[N]; 
void sieve() 
{
    memset(prime, true, sizeof(prime)); 
    prime[0] = prime[1] = false;
    for (int p = 2; p*p < N; p++) 
    { 
        if (prime[p] == true) 
        {
            for (int i = p*p; i < N; i += p) 
                prime[i] = false; 
        } 
    } 
}
