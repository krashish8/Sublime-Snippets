vector<tuple<int,int,int>> edges;
int dis[N];

int n, x;
for (int i = 1; i <= n; ++i) dis[i] = inf;
dis[x] = 0;
for (int i = 1; i < n-1; ++i)
{
	for (auto e: edges) {
		int a, b, w;
		tie(a,b,w) = e;
		dis[b] = min(dis[b], dis[a]+w);
	}
}
