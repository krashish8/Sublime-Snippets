std::ostream& operator<<(std::ostream& os, SegTree s)
{
    os << "[";
    for (int i = 1; i <= 4 * s.N; i++) {
        os << "[";
        for (int j = 1; j <= 4 * s.M; j++) {
            os << s.st[i][j].val;
            if (j != 4*s.M)
                os << ", ";
        }
        os << "]";
        if (i != 4 * s.N)
            os << ", ";
    }
    os << "]";
    return os;
}
