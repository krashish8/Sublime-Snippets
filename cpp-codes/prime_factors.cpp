map<int,int> mm;
set<int> s;

//s.clear();
//mm.clear(); Use these before successive iterations

vector<int> primeFactor(int n) 
{ 
    vector<int> v;
    while (n%2 == 0) 
    { 
        v.push_back(2);
        n = n/2; 
    }  
    for (int i = 3; i <= sqrt(n); i = i+2) 
    { 
        while (n%i == 0) 
        { 
            v.pb(i);  
            n = n/i; 
        } 
    } 
    if (n > 2) 
        v.push_back(n);
    for (int i = 0; i < v.size(); ++i)
    {
        s.insert(v[i]);
        mm[v[i]]++;
    }
    return v;
}
