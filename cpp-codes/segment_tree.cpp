struct SegTree
{
	struct data
	{
		int mn, val;

		// ----------------------
		data() : mn(1e9), val(0) {};
		template <typename T>
		void apply(T v) {
			val = v;
		}
	};

	int N;
	vector<data> st;
	vector<int> lazy;
	vector<bool> islazy;

	SegTree() {}

	SegTree(int _N) : N(_N) {
		st.resize(4 * N + 5);
		lazy.assign(4 * N + 5, 0);
		islazy.assign(4 * N + 5, 0);
	}

	inline void merge(data &cur, const data &l, const data &r) 
	{
		// ----------------------
		cur.mn = min(l.mn, r.mn);
	}

	inline void pushdown(int node, int l, int r)
	{
		if (islazy[node]) {
			if (l != r) {
				islazy[node*2] = 1;
				islazy[node*2 + 1] = 1;
				// ------------------------
				lazy[node*2] = lazy[node];
				lazy[node*2 + 1] = lazy[node];
			}
			// --------------------
			st[node].mn = lazy[node];
			lazy[node] = 0;
			islazy[node] = 0;
		}
	}

	void build(int node, int l, int r)
	{
		pushdown(node, l, r);
		if(l == r)
		{
			// -----------------------
			st[node].mn = 1e9;
			return;
		}
		int mid = (l + r) / 2;
		build (node*2, l, mid);
		build (node*2 + 1, mid + 1, r);
		merge (st[node], st[node*2], st[node*2+1]);
	}

	template <typename T>
	void build(int node, int l, int r, vector<T> &v)
	{
		pushdown(node, l, r);
		if(l == r)
		{
			// -----------------------
			if (l < (int)v.size()) st[node].apply(v[l]);
			else st[node].apply(0);
			return;
		}
		int mid = (l + r) / 2;
		build (node*2, l, mid, v);
		build (node*2 + 1, mid + 1, r, v);
		merge (st[node], st[node*2], st[node*2+1]);
	}

	data query(int node, int l, int r, int i, int j)
	{
		pushdown(node, l, r);
		if(j < l || i > r)
			return data();
		if(i <= l && r <= j)
			return st[node];
		int mid = (l + r)/2;
		data left = query (node*2, l, mid, i, j);
		data right = query (node*2 + 1, mid + 1, r, i, j);
		data cur;
		merge (cur, left, right);
		return cur;
	}

	data pquery(int node, int l, int r, int pos)
	{
		pushdown(node, l, r);
		if(l == r)
			return st[node];
		int mid = (l + r)/2;
		if(pos <= mid)
			return pquery(node*2, l, mid, pos);
		else
			return pquery(node*2 + 1, mid + 1, r, pos);
	}	

	void update(int node, int l, int r, int i, int j, int val)
	{
		pushdown (node, l, r);
		if (j < l || i > r)
			return;
		if(i <= l && r <= j)
		{
			islazy[node] = 1;
			// --------------------
			lazy[node] = val;
			pushdown(node, l, r);
			return;
		}
		int mid = (l + r)/2;
		update (node*2, l, mid, i, j, val);
		update (node*2 + 1, mid + 1, r, i, j, val);
		merge (st[node], st[node*2], st[node*2 + 1]);
	}

	void pupdate(int node, int l, int r, int pos, int val)
	{
		pushdown(node, l, r);
		if(l == r)
		{
			islazy[node] = 1;
			// ----------------
			lazy[node] = val;
			pushdown(node, l, r);
			return;
		}
		int mid = (l + r)/2;
		if(pos <= mid)
			pupdate(node*2, l, mid, pos, val);
		else
			pupdate(node*2 + 1, mid + 1, r, pos, val);
		merge (st[node], st[node*2], st[node*2 + 1]);
	}

	void build() {
		build(1, 1, N);
	}

	template <typename T>
	void build(vector<T> &v) {
		build(1, 1, N, v);
	}

	data query(int l, int r)
	{
		return query(1, 1, N, l, r);
	}

	data query(int pos)
	{
		return pquery(1, 1, N, pos);
	}

	void update(int l, int r, int val)
	{
		update(1, 1, N, l, r, val);
	}

	void update(int pos, int val)
	{
		pupdate(1, 1, N, pos, val);
	}
};
