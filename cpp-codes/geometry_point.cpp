const double EPS = 1e-6;
const double PI = acos(-1);

#define ptype double

struct point {
    ptype x, y;

    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}

    point& operator+=(const point &p) { x += p.x; y += p.y; return *this; }
    point& operator-=(const point &p) { x -= p.x; y -= p.y; return *this; }
    point& operator*=(ptype a) { x *= a; y *= a; return *this; }
    point& operator/=(ptype a) { x /= a; y /= a; return *this; }

    point operator+(const point &p) const { return point(*this) += p; }
    point operator-(const point &p) const { return point(*this) -= p; }
    point operator*(ptype a) const { return point(*this) *= a; }
    point operator/(ptype a) const { return point(*this) /= a; }
    bool operator==(const point &p) { return (x == p.x && y == p.y); }
    bool operator!=(const point &p) { return !(x == p.x && y == p.y); }
};

point operator*(ptype a, point p) { return p * a; }

ostream& operator<<(ostream &os, const point &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

ptype dot(point a, point b) { return a.x * b.x + a.y * b.y; }
ptype cross(point a, point b) { return a.x * b.y - a.y * b.x; }
ptype dist2(point a, point b) { return dot(a - b, a - b); }
ptype abs2(point a) { return a.x * a.x + a.y * a.y; }

// Rotate a point CCW or CW
point rotateCCW90(point p) { return point(-p.y, p.x); }
point rotateCW90(point p) { return point(p.y, -p.x); }
point rotateCCW(point p, double t) {
    return point(p.x*cos(t) - p.y*sin(t), p.x*sin(t) + p.y*cos(t));
}
