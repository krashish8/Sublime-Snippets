void dfs(int n) {
	if (vis[n]) return;
	vis[n] = 1;
	for (auto i : g[n])
		dfs(i);
}
