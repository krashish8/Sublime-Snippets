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

void randtree(int n) {
	int prufer[n-2];
    rep(i,0,n-2){
        prufer[i] = rand(1,n);
    }
    int m = n-2;
    int vertices = m + 2; 
    int vertex_set[vertices]; 
    for (int i = 0; i < vertices; i++) 
        vertex_set[i] = 0; 
    for (int i = 0; i < vertices - 2; i++) 
        vertex_set[prufer[i] - 1] += 1; 
    int j = 0; 
    for (int i = 0; i < vertices - 2; i++) { 
        for (j = 0; j < vertices; j++) { 
            if (vertex_set[j] == 0) { 
                vertex_set[j] = -1; 
                cout << (j + 1) << " "
                     << prufer[i] << '\n'; 
                vertex_set[prufer[i] - 1]--; 
                break; 
            } 
        } 
    } 
    j = 0; 
    for (int i = 0; i < vertices; i++) { 
        if (vertex_set[i] == 0 && j == 0) { 
            cout << (i + 1) << " "; 
            j++; 
        } 
        else if (vertex_set[i] == 0 && j == 1) 
            cout << (i + 1) << "\n"; 
    }
}
