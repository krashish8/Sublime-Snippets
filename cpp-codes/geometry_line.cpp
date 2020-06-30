// Orthogonal projection of a point c onto line a-b
point projectPointLine(point a, point b, point c) {
    assert(a != b);
    return a + (b - a) * dot(c-a, b-a) / dot(b-a, b-a);
}

// Nearest point on line segment a-b from point c
point nearestPointLineSegment(point a, point b, point c) {
    double r = dot(b - a, b - a);
    if (abs(r) < EPS) return a;
    r = dot(c-a, b-a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a) * r;
}

// Distance from point c to line a-b
double distPointLine(point a, point b, point c) {
    return sqrtl(dist2(c, projectPointLine(a, b, c)));
}

// Distance from point c to line segment a-b
double distPointLineSegment(point a, point b, point c) {
    return sqrtl(dist2(c, nearestPointLineSegment(a, b, c)));
}

// 3D: Distance between point(x,y,z) and plane ax+by+cz = d
double distPointPlane(double x, double y, double z, double a, double b, double c, double d) {
    return abs(a*x + b*y + c*z - d) / sqrtl(a*a + b*b + c*c);
}

// Whether line a-b and c-d are parallel or collinear
bool isLinesParallel(point a, point b, point c, point d) {
    return abs(cross(b-a, c-d)) < EPS;
}
bool isLinesCollinear(point a, point b, point c, point d) {
    return isLinesParallel(a, b, c, d) && abs(cross(a-b, a-c)) < EPS && abs(cross(c-d, c-a)) < EPS;
}

// Whether line segments a-b and c-d intersect
bool isSegmentsIntersect(point a, point b, point c, point d) {
    if (isLinesCollinear(a, b, c, d)) {
        if (dist2(a, c) < EPS || dist2(a, d) < EPS || dist2(b, c) < EPS || dist2(b, d) < EPS)
            return true;
        if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
            return false;
        return true;
    }
    if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
    if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
    return true;
}

// compute intersection point of line a-b and c-d (assuming unique intersection exists)
// For segment intersection, check if segments intersect first
point computeLineIntersection(point a, point b, point c, point d) {
    b = b - a;
    d = c - d;
    c = c - a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b*cross(c, d)/cross(b, d);
}


// Whether b lies in the ray starting from a in the direction v
bool isRayOnPoint(point a, point v, point b) {
    b = b - a;
    // A and B in the same line
    if(abs(b.x*v.y - b.y*v.x) < EPS) {
        // in the same ray
        if(b.x*v.x >= -EPS && b.y*v.y >= -EPS)
            return 1;
        return 0;
    }
    return 0;
}

int sign(point a, point b, point c) {
    return ((cross(b-a, c-b) < 0) ? -1 : 1);
}


// Line: ax + by + c = 0
struct line {
    double a, b, c;
    line() {}
    line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
};

bool areParallel(line l1, line l2) { return abs(l1.a - l2.a) < EPS && abs(l1.b - l2.b) < EPS; }
bool areSame(line l1, line l2) { return areParallel(l1, l2) && abs(l1.c - l2.c) < EPS; }

