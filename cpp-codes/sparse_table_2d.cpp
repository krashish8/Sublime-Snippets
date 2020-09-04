// usage:
//     auto fun = [&](int i, int j) { return min(i, j); };
//     SparseTable<int, decltype(fun)> st(a, fun);
// or:
//     SparseTable<int> st(a, [&](int i, int j) { return min(i, j); });
template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable2D {
    int n, m;
    vector<vector<vector<vector<T>>>> mat;
    F func;

    SparseTable2D(const vector<vector<T>>& a, const F& f) : func(f) {
        n = a.size();
        m = a[0].size();
        int logn = 32 - __builtin_clz(n);
        int logm = 32 - __builtin_clz(m);
        mat.resize(logn);
        for (int i = 0; i < mat.size(); i++)
            mat[i].resize(logm);
        // mat[jr][jc][ir][ic];
        for (int jr = 0; jr < logn; jr++) {
            for (int jc = 0; jc < logm; jc++) {
                mat[jr][jc].resize(n);
                for (int ir = 0; ir < n; ir++)
                    mat[jr][jc][ir].resize(m);
            }
        }
        mat[0][0] = a;
        for (int ir = 0; ir < n; ir++) {
            for (int jc = 1; jc < logm; jc++) {
                for (int ic = 0; ic + (1 << (jc - 1)) < m; ic++) {
                    mat[0][jc][ir][ic] = func(mat[0][jc-1][ir][ic], mat[0][jc-1][ir][ic + (1 << (jc - 1))]);
                }
            }
        }
        for (int jr = 1; jr < logn; jr++) {
            for (int ir = 0; ir + (1 << (jr-1)) < n; ir++) {
                for (int jc = 0; jc < logm; jc++) {
                    for (int ic = 0; ic < m; ic++) {
                        mat[jr][jc][ir][ic] = func(mat[jr-1][jc][ir][ic], mat[jr-1][jc][ir + (1 << (jr-1))][ic]);
                    }
                }
            }
        }
    }

    T get(int x1, int y1, int x2, int y2) const {
        assert(0 <= x1 && x1 <= x2 && x2 <= n - 1);
        assert(0 <= y1 && y1 <= y2 && y2 <= m - 1);
        int logx = 32 - __builtin_clz(x2 - x1 + 1) - 1;
        int logy = 32 - __builtin_clz(y2 - y1 + 1) - 1;
        int r1 = func(mat[logx][logy][x1][y1], mat[logx][logy][x1][y2 - (1 << logy) + 1]);
        int r2 = func(mat[logx][logy][x2 - (1 << logx) + 1][y1], mat[logx][logy][x2 - (1 << logx) + 1][y2 - (1 << logy) + 1]);
        return func(r1, r2);
    }
};
