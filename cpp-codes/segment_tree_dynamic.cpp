struct node {
    int left = 0, right = 0;
    int val = 0;
}st[40*N];
 
void merge(node &cur, node &l, node &r) {
    cur.val = l.val + r.val;
}
 
int cnt = 1;
 
void update(int x, int l, int r, int pos, int val) {
    if (pos > r || pos < l) return;
    if (l == r) {
        st[x].val += val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        if (st[x].left == 0) st[x].left = ++cnt;
        update(st[x].left, l, mid, pos, val);
    }
    else {
        if (st[x].right == 0) st[x].right = ++cnt;
        update(st[x].right, mid + 1, r, pos, val);
    }
    st[x].val += val;
}
 
node query(int x, int l, int r, int s, int e) {
    if (r < s || l > e) return node();
    if (s <= l && r <= e) return st[x];
    int mid = (l + r) / 2;
    if (st[x].left == 0) st[x].left = ++cnt;
    if (st[x].right == 0) st[x].right = ++cnt;
    node left = query(st[x].left, l, mid, s, e);
    node right = query(st[x].right, mid + 1, r, s, e);
    node cur;
    merge(cur, left, right);
    return cur;
}
