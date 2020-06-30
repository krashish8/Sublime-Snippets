// answer all queries starting in first block, then second block, etc. (offline)
// for queries starting in one block, order them in ascending order of right index
// l in one block: unordered (√N * Q queries)
// r in one block: ordered in ascending order (N * √N blocks)

int a[N];
const int S = sqrt(N);

inline bool mo_sort(const pair<pii, int> &a, const pair<pii, int> &b) {
    int al = a.first.first, ar = a.first.second;
    int bl = b.first.first, br = b.first.second;
    if (al/S != bl/S)
        return al < bl;
    if (al/S & 1)
        return ar < br;
    else
        return ar > br;
}

int ans = 0;
int fans[N];
unordered_map<int, int> mp;

inline void add(int pos) {
    mp[a[pos]]++;
    if (mp[a[pos]] == a[pos]) ans++;
    if (mp[a[pos]] == a[pos] + 1) ans--;
}

inline void remove(int pos) {
    mp[a[pos]]--;
    if (mp[a[pos]] == a[pos]) ans++;
    if (mp[a[pos]] == a[pos] - 1) ans--;
}

    int n, m;
    cin >> n >> m;
    vector<pair<pii, int>> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        q.push_back({{a, b}, i});
    }
    sort(q.begin(), q.end(), mo_sort);
    int cur_l = 0, cur_r = -1;
    for (int i = 0; i < m; i++) {
        int l = q[i].first.first;
        int r = q[i].first.second;
        l--;
        r--;
        while (cur_l > l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > r) {
            remove(cur_r);
            cur_r--;
        }
        fans[q[i].second] = ans;
    }
    for (int i = 0; i < m; i++)
        cout << fans[i] << endl;
