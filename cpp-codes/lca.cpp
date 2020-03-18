int timer = 1, in[N], out[N], up[N][M], l;
 
void dfs(int n, int p) {
    in[n] = timer++;
    up[n][0] = p;
    for (int i = 1; i <= l; i++) {
        up[n][i] = up[up[n][i-1]][i-1];
    }
    for (auto i: g[n]) {
        if (i != p)
            dfs(i, n);
    }
    out[n] = timer++;
}
 
bool is_ancestor(int u, int v)
{
    return in[u] <= in[v] && out[u] >= out[v];
}
 
int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = l; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}
