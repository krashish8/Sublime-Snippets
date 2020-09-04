vector<int> divisors(int n) 
{ 
    vector<int> v;
    for (int i=1; i<=sqrt(n); i++) 
    {
        if (n%i == 0) 
        {
            v.push_back(i);
        } 
    }
    for (int i = v.size()-1; i >=0 ; i--) {
        if(v[i]*v[i]==n) continue;
        v.push_back(n/v[i]);
    }
    return v;
}
