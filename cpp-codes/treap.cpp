mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r){
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

// -------------------------- COMMON FOR REGULAR AND IMPLICIT --------------------------

struct node {
    node *left, *right;
    int val, prior, lazy, cnt;

    node(int _val) {
        left = right = NULL;
        val = _val;
        prior = rand(1, 2e9);
        lazy = 0;
        cnt = 1;
    }
};

int count(node *t) {
    return (t == NULL) ? 0 : t->cnt;
}

// change push() and update() for lazy propagation (implicit)
void push(node *t) {
    if (!t || !t->lazy) return;
}

// update the size (or other values) during split and merge (after recursion)
// (Everything is done using split and merge)
void update(node *t) {
    if (!t) return;
    t->cnt = count(t->left) + count(t->right) + 1;
    push(t);
}

// when all the val of one treap is less than the val of other treap (regular and implicit)
void merge(node *&t, node *l, node *r) {
    push(l);
    push(r);
    if (l == NULL) t = r;
    else if (r == NULL) t = l;
    else if (l -> prior >= r->prior) {
        merge(l->right, l->right, r);
        t = l;
    }
    else {
        merge(r->left, l, r->left);
        t = r;
    }
    update(t);
}

// 1 indexed
node *find_kth(node *&t, int k) {
    push(t);
    if (k - count(t->left) == 1) return t;
    else if (k <= count(t->left)) return find_kth(t->left, k);
    else return find_kth(t->right, k - count(t->left) - 1);
}

void printtreap(node* t) {
    if (!t) return;
    printtreap(t->left);
    cerr << t->val << " ";
    printtreap(t->right);
}

// -------------------------- ONLY FOR REGULAR TREAP --------------------------

// divide tree into l and r with all val of l <= val, and all val of r > val
void split(node *t, node *&l, node *&r, int val) {
    if (t == NULL) {
        l = r = NULL;
        return;
    }
    if (t->val <= val) {
        split(t->right, t->right, r, val);
        l = t;
    }
    else {
        split(t->left, l, t->left, val);
        r = t;
    }
    update(t);
}

void insert(node *&t, int val) {
    if (t == NULL) {
        t = new node(val);
        return;
    }
    node *l = NULL, *r = NULL;
    split(t, l, r, val);
    node *n = new node(val);
    merge(l, l, n);
    merge(t, l, r);
}

void erase(node *&t, int val) {
    if (t == NULL) {
        return;
    }
    node *l = NULL, *r = NULL, *ll = NULL, *lr = NULL;
    split(t, l, r, val);
    split(l, ll, lr, val - 1);
    // erasing only one
    if (count(lr) > 1) {
        merge(lr, lr->left, lr->right);
        merge(ll, ll, lr);
    }
    merge(t, ll, r);
}

bool find_val(node *t, int val) {
    if (t == NULL) return false;
    if (t -> val == val) return true;
    else if (t->val < val) return find_val(t->right, val);
    else return find_val(t->left, val);
}

// -------------------------- ONLY FOR IMPLICIT TREAP --------------------------

void split_implicit(node *t, node *&l, node *&r, int pos) {
    if (t == NULL) {
        l = r = NULL;
        return;
    }
    if (count(t->left) + 1 <= pos) {
        split(t->right, t->right, r, pos - count(t->left) - 1);
        l = t;
    }
    else {
        split(t->left, l, t->left, pos);
        r = t;
    }
    update(t);
}

void insert_implicit(node *&t, int val, int pos) {
    push(t);
    node *l = NULL, *r = NULL;
    split_implicit(t, l, r, pos - 1);
    node *n = new node(val);
    merge(l, l, n);
    merge(t, l, r);
}

void erase_implicit(node *&t, int pos) {
    push(t);
    node *l = NULL, *r = NULL, *ll = NULL, *lr = NULL;
    split_implicit(t, l, r, pos);
    split_implicit(l, ll, lr, pos - 1);
    merge(t, ll, r);
}
