const int LOGN = 18;

vector<int> g[N];
int dep[N], dp[LOGN][N];
bool mark[N];
int sz[N], par[N];

// Traversal is started from node 1.
// dp[i][x]: moving towards parent node = x + 2^i node in main tree
// dep[x]: depth of node x in main tree, descending from parent

void dfs2(int u, int p) {
    for (auto v : g[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dp[0][v] = u;
        dfs2(v, u);
    }
}

void preprocess(int n) {
    dep[1] = 0;
    dp[0][1] = 1;
    dfs2(1, 0);
    for (int k = 1; k < LOGN; k++) {
        for (int i = 1; i <= n; i++) {
            dp[k][i] = dp[k-1][dp[k-1][i]];
        }
    }
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int d = dep[v] - dep[u];
    for (int k = LOGN - 1; k >= 0; k--) {
        if (d & (1 << k))
            v = dp[k][v];
    }
    if (u == v) return u;
    for (int k = LOGN - 1; k >= 0; k--) {
        if (dp[k][u] != dp[k][v])
            u = dp[k][u], v = dp[k][v];
    }
    return dp[0][u];
}

int dis(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}

// --> Centroid Decomposition

int dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : g[u]) {
        if (v == p || mark[v]) continue;
        sz[u] += dfs(v, u);
    }
    return sz[u];
}

int centroid(int u, int p, int n) {
    for (auto v : g[u]) {
        if (v == p || mark[v]) continue;
        if (sz[v] > n / 2) return centroid(v, u, n);
    }
    return u;
}

void decompose(int u, int p) {
    int n = dfs(u, p);
    int c = centroid(u, p, n);
    mark[c] = 1;
    if (p == 0) p = c;
    par[c] = p;
    for (auto v : g[c]) {
        if (!mark[v])
            decompose(v, c);
    }
}
