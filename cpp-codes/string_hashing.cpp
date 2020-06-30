struct Hash 
{
    vector<int> hash;
    vector<int> pows;
    int P;
    int MOD;

    Hash () {}

    template <typename T>
    Hash(const T &s, int _Prime=31, int _MOD=1000000007) : P(_Prime), MOD(_MOD) 
    {
        int n = s.size();
        pows.resize(n+1, 0);
        hash.resize(n+1, 0);
        pows[0] = 1;
        hash[0] = s[0] - 'a' + 1;
        for (int i = 1; i < n; i++) {
            hash[i] = (s[i] - 'a' + 1 + hash[i-1] * P) % MOD;
            pows[i] = (pows[i-1] * P) % MOD;
        }
    }

    int get_hash(int l, int r) 
    {
        if (l == 0) return (hash[r]);
        int ans = (hash[r] - hash[l-1]*pows[r-l+1]%MOD + MOD) % MOD;
        ans %= MOD;
        return ans;
    }
};
