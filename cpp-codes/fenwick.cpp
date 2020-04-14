template <typename T>
struct Fenwick {
    vector<T> bit, bit2;
    int n;

    Fenwick(int _n) : n(_n) {
        bit.resize(n);
        bit2.resize(n);
    }

    // Increment the value of node
    void update(int x, T v) {
        while (x < n) {
            bit[x] += v;
            x += (x & -x); // For 0 based indexing, x |= (x + 1);
        }
    }

    // Get prefix sum from [1 ... x]
    T prefsum(int x) {
        T v{};
        while (x > 0) {
            v += bit[x];
            x -= (x & -x); // For 0 based indexing, x = (x & (x + 1)) - 1; and x >= 0
        }
        return v;
    }

    T sum(int l, int r) {
        return prefsum(r) - prefsum(l-1);
    }

    // ----------------------------------------------------------------------------

    void update(int x, T v, vector<T> &_bit) {
        while (x < n) {
            _bit[x] += v;
            x += (x & -x); // For 0 based indexing, x |= (x + 1);
        }
    }

    T prefsum(int x, vector<T> &_bit) {
        T v{};
        while (x > 0) {
            v += _bit[x];
            x -= (x & -x); // For 0 based indexing, x = (x & (x + 1)) - 1; and x >= 0
        }
        return v;
    }

    // Increment range from [l ... r]
    void rupdate(int l, int r, T v) {
        update(l, v, bit);
        update(r+1, -v, bit);

        update(l, -(l-1)*v, bit2);
        update(r+1, (l-1)*v, bit2);
        update(r+1, (r-l+1)*v, bit2);
    }

    // Prefix sum in case of range update
    T rprefsum(int x) {
        return prefsum(x, bit)*x + prefsum(x, bit2);
    }

    T rsum(int l, int r) {
        return rprefsum(r) - rprefsum(l-1);
    }
};
