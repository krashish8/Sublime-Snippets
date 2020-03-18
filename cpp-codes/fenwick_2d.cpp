template <typename T>
struct Fenwick2d {
    vector< vector<T> > bit;
    int n, m;

    Fenwick2d(int _n, int _m) : n(_n), m(_m) {
        bit.resize(n);
        for (int i = 0; i < n; i++) {
            bit[i].resize(m);
        }
    }

    void update(int i, int j, T v) {
        int x = i;
        while (x < n) {
            int y = j;
            while (y < m) {
                bit[x][y] += v;
                y += (y & -y);
            }
            x += (x & -x);
        }
    }

    T prefsum(int i, int j) {
        T v{};
        int x = i;
        while (x > 0) {
            int y = j;
            while (y > 0) {
                v += bit[x][y];
                y -= (y & -y);
            }
            x -= (x & -x);
        }
        return v;
    }

    T sum(int l1, int r1, int l2, int r2) {
        return prefsum(l2, r2) - prefsum(l2, r1-1) - prefsum(l1-1, r2) + prefsum(l1-1, r1-1);
    }
};
