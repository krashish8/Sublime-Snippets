vector<int> g[N];
int sz[N], par[N], nxt[N], dep[N];
int in[N], out[N], timer = 1;

void dfs(int u, int p) {
    par[u] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;
    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[v] += sz[u];
        if (sz[v] > sz[g[u][0]])
            swap(v, g[u][0]);
    }
}

void hld(int u, int p) {
    in[u] = timer++;
    for (auto v : g[u]) {
        if (v == p) continue;
        nxt[v] = (u == g[u][0] ? nxt[u] : v);
        hld(v, u);
    }
    out[u] = timer;
}

int lca(int u, int v) {
    while (nxt[u] != nxt[v]) {
        if (dep[nxt[u]] > dep[nxt[v]]) u = par[nxt[u]];
        else v = par[nxt[v]];
    }
    if (dep[u] > dep[v]) return v;
    else return u;
}

// Subtree query: in[v], out[v]
// Path query: in[nxt[v]], in[v]
