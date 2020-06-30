// Whether point is in a possibly non-convex polygon (by William Randolph Franklin)
// returns 1: strictly interior points, 0: strictly exterior points, 0 or 1: remaining
// It is possible to convert this test into an exact test using integer arithmetic
// by taking care of division appropriately (making sure to deal with signs properly)
// and then by writing exact tests for checking point on polygon boundary
bool isPointInPolygon(const vector<point> &p, point q) {
    bool c = 0;
    for (int i = 0; i < p.size(); i++){
        int j = (i+1)%p.size();
        if ((p[i].y <= q.y && q.y < p[j].y || p[j].y <= q.y && q.y < p[i].y) &&
              q.x < (p[i].x + (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y)))
            c = !c;
    }
    return c;
}

// Whether the point is on the boundary of polygon
bool isPointOnPolygon(const vector<point> &p, point q) {
    for (int i = 0; i < p.size(); i++)
        if (dist2(nearestPointLineSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
            return true;
    return false;
}


// Compute area or centroid of a possibly non-convex polygon,
// assuming that coordinates are listed in CW or CCW order.
// Centroid: "centre of gravity" or "centre of mass".
double computeSignedAreaOrdered(const vector<point> &p) {
    double area = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return area / 2.0;
}
double computeArea(const vector<point> &p) {
    return abs(computeSignedAreaOrdered(p));
}
point computeCentroid(const vector<point> &p) {
    point c(0,0);
    double scale = 6.0 * computeSignedAreaOrdered(p);
    for (int i = 0; i < p.size(); i++){
        int j = (i+1) % p.size();
        c = c + (p[i]+p[j]) * (p[i].x*p[j].y - p[j].x*p[i].y);
    }
    return c / scale;
}

// Whether a given polygon (in CW or CCW order) is simple
bool isSimpleOrdered(const vector<point> &p) {
    for (int i = 0; i < p.size(); i++) {
        for (int k = i + 1; k < p.size(); k++) {
            int j = (i+1) % p.size();
            int l = (k+1) % p.size();
            if (i == l || j == k)
                continue ;
            if (isSegmentsIntersect(p[i], p[j], p[k], p[l]))
                return false;
        }
    }
    return true;
}

// QUADRILATERALS
/*
    Area of trapezium : 0.5 * (w1 + w2) * h
        w1 and w2 are parallel edges and h is height
    Area of kite : 0.5 * d1 * d2
*/

// Whether angle ABC is a right-angle
int isOrthogonal(point &a, point &b, point &c) {
    return (b.x-a.x) * (b.x-c.x) + (b.y-a.y) * (b.y-c.y) == 0;
}

// Whether ABCD forms a rectangle, in any orientation
int isRectangleAnyOrder(point &a, point &b, point &c, point &d)
{
    auto isRectangle = [](point &a, point &b, point &c, point &d) {
        return isOrthogonal(a, b, c) && isOrthogonal(b, c, d) && isOrthogonal(c, d, a);
    };
    return isRectangle(a, b, c, d) || isRectangle(b, c, a, d) || isRectangle(c, a, b, d);
}

// Whether ABCD forms a square, in any orientation
int isSquareAnyOrder(point &a, point &b, point &c, point &d)
{
    auto isEqualDist = [](point &a, point &b, point &c) {
        return dist2(a, b) == dist2(b, c);
    };
    return isRectangleAnyOrder(a, b, c, d) &&
        isEqualDist(a,b,c) && isEqualDist(b,c,d) && isEqualDist(c,d,a);
}

