mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r){
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

double randr(int l, int r) {
    uniform_real_distribution<double> urd(l, r);
    return urd(rng);
}

// Random n numbers between l and r
vector<int> randint(int l, int r, int n) {
    vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(rand(l, r));
    }
    return v;
}
 
//Random n real numbers between l and r
vector<double> randreal(int l, int r, int n) {
    vector<double> v;
    for (int i = 0; i < n; i++) {
        v.push_back(randr(l, r));
    }
    return v;
}

// Random n strings of length l
vector<string> randstr(int l, int n) {
    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s = "";
        for(int j = 0; j < l; j++) {
            int r = rand(1, 3);
            if (r == 1) s += (char)rand('a', 'z');
            else if (r == 2) s += (char)rand('A', 'Z');
            else if (r == 3) s += (char)rand('0', '9');
        }
        v.push_back(s);
    }
    return v;
}

// Random n strings of max length l
vector<string> randstrmx(int mxlen, int n) {
    vector<string> v;
    for (int i = 0; i < n; i++) {
        int l = rand(1, mxlen);
        vector<string> s = randstr(l, 1);
        v.push_back(s[0]);
    }
    return v;
} 

// Random tree, vertex starts from st
vector<pair<int, int>> randtree(int n, int st = 1) {
    vector<int> code(n - 2);
    for (int i = 0; i < n - 2; i++)
        code[i] = rand(1, n);
    vector<int> degree(n + 1, 1);
    for (int i : code)
        degree[i]++;

    int ptr = 1;
    while (degree[ptr] != 1)
        ptr++;
    int leaf = ptr;

    vector<pair<int, int>> v;
    for (int vertex : code) {
        v.push_back({leaf, vertex});
        if (--degree[vertex] == 1 && vertex < ptr) {
            leaf = vertex;
        } else {
            ptr++;
            while (degree[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    v.push_back({leaf, n});
    shuffle(v.begin(), v.end(), rng);
    return v;
}

// Random unweighted graph, no self loops
vector<pair<int, int>> generate_unweighted_graph(int n, int m) {
    assert(m <= (long long)n * (n - 1) / 2); // avoiding self loops, multiple edges
    set<pair<int, int>> s;
    while (s.size() < m) {
        int first = rand(1, n);
        int second = rand(1, n);
        if (first == second) {
            continue; // avoid self loops
        }
        s.insert({first, second});
    }
    vector<pair<int, int>> v(s.begin(), s.end());
    shuffle(v.begin(), v.end(), rng);
    return v;
}
