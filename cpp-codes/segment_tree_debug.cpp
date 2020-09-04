std::ostream& operator<<(std::ostream& os, SegTree s)
{
    os << "[";
    for (int i = 1; i <= 4 * s.N; i++) {
        os << s.st[i].val;
        if (i != 4*s.N)
            os << ", ";
    }
    os << "]";
    return os;
}

