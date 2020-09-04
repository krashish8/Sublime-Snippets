// for Strongly Connected components

void dfs(int n) {
    if (vis[n]) return;
    vis[n] = 1;
    for (auto i : g[n])     // a --> b
        dfs(i);
    s.push(n);
}
 
void dfs2(int n) {
    if (vis[n]) return;
    vis[n] = 1;
    comp.push_back(n);
    for (auto i : gr[n])    // b --> a
        dfs2(i);
}

    for (int i = 1; i <= n; i++) {
        dfs(i);
    }
    memset(vis, 0, sizeof(vis));
    while (!s.empty()) {
        int t = s.top();
        s.pop();
        comp.clear();
        if (!vis[t]) dfs2(t);
    }
