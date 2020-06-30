// compute centre of circle with three points
point computeCircleCentre(point a, point b, point c) {
    b = (a+b) / 2;
    c = (a+c) / 2;
    return computeLineIntersection(b, b + rotateCW90(a-b), c, c + rotateCW90(a-c));
}

// Intersection of line a-b with circled centred at c, radius r
vector<point> circleLineIntersection(point a, point b, point c, double r) {
    vector<point> ret;
    b = b - a;
    a = a - c;
    double A = dot(b, b);
    double B = dot(a, b);
    double C = dot(a, a) - r*r;
    double D = B*B - A*C;
    if (D < -EPS)
        return ret;
    ret.push_back(c + a + b * (-B+sqrtl(D+EPS)) / A);
    if (D > EPS)
        ret.push_back(c + a + b * (-B-sqrtl(D)) / A);
    return ret;
}

// Intersection of circle(centre a, radius r) with circle(centre b, radius R)
vector<point> circleCircleIntersection(point a, point b, double r,  double R) {
    vector<point> ret;
    double d = sqrtl(dist2(a, b));
    if (d > r+R || d+min(r, R) < max(r, R))
        return ret;
    double x = (d*d - R*R + r*r) / (2*d);
    double y = sqrtl(r*r - x*x);
    point v = (b-a)/d;
    ret.push_back(a + v*x + rotateCCW90(v)*y);
    if (y > 0)
        ret.push_back(a + v*x - rotateCCW90(v)*y);
    return ret;
}

// Area of arc formed by circle and line a-c and b-c
double arcArea(point a, point b, point c, double r) {
    double cosa = dot(a-c,b-c) / ( sqrt(abs2(a-c)) * sqrt(abs2(b-c)) );
    double ang = acos(cosa);
    if(ang > 2 * PI)
        ang = 2 * PI - ang;
    return 0.5 * r * r * ang;
}

// Area of intersection of triangle a1-a2-c and circle(c, r)
double triangleCircleArea (point a1, point a2, point c, double r) {
    double ans = 0;
    double d1 = dist2(a1, c), d2 = dist2(a2, c);
    if(d1 > d2) swap(d1, d2), swap(a1, a2);
    if(d2 <= r * r) {
        ans = 0.5 * abs(cross(a1-c, a2-c));
    }
    else if(d1 <= r*r) {
        auto vv = circleLineIntersection(a1,a2,c,r);
        point C = vv[0];
        if(vv.size() > 1 && dot(vv[1]-a1, vv[1]-a2) < 0)
            C = vv[1];
        vv = circleLineIntersection(a2, c, c, r);
        point D = vv[0];
        if(vv.size() > 1 && dot(vv[1]-a2, vv[1]-c) < 0)
            D = vv[1];
        ans = arcArea(C, D, c, r) + 0.5*abs(cross(C-c, a1-c));
    }
    else {
        auto vv = circleLineIntersection(a1, a2, c, r);
        if(vv.size() <= 1 || dot(a1-vv[0], a2-vv[0]) > 0) {
            ans = arcArea(a1, a2, c, r);
        }
        else {
            if(dist2(a1, vv[1]) < dist2(a1, vv[0]))
                swap(vv[0], vv[1]);
            ans = arcArea(a1, vv[0], c, r) + arcArea(a2, vv[1], c, r) +
                    0.5 * abs(cross(vv[0]-c, vv[1]-c));
        }
    }
    return abs(ans);
}


// Calculate intersection area of polygon and circle
double polyCircleArea(vector<point> &a, point c, double r) {
    int n = a.size();
    if(n <= 2) return 0;
    double ans=0;
    for (int i = 0; i < n; i++)
        ans += triangleCircleArea(a[i], a[(i+1)%n], c, r) * sign(c,a[i],a[(i+1)%n]);
    return abs(ans);
}

// Circle with centre: point(c) and radius r
struct Circle: point {
    double r;
    Circle() {}
    Circle(point c, double r) : point(c.x, c.y), r(r) {}

    bool strictContains(point p) { return dist2((*this), p) < r*r; }
    bool onBorder(point p) { return abs(dist2((*this), p) - r*r)<EPS; }
    bool contains(point p) { return strictContains(p) || onBorder(p); }
};

// Find common tangents to 2 circles
// Returns vector containing all common tangents
vector<line> tangents(Circle a, Circle b) {
    auto tangents = [](point c, double r1, double r2, vector<line> &ans) {
        double r = r2 - r1;
        double z = c.x * c.x + c.y * c.y;
        double d = z - r * r;
        if (d < -EPS) return;
        d = sqrt(abs(d));
        line l((c.x*r + c.y*d) / z, (c.y*r - c.x*d) / z, r1);
        ans.push_back(l);
    };
    assert(a != b);
    vector<line> ans;
    ans.clear();
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            tangents(b-a, a.r * i, b.r * j, ans);
        }
    }
    for(int i = 0; i < (int)ans.size(); i++) {
        ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;
    }
    vector<line> ret;
    for (int i = 0; i < (int)ans.size(); i++) {
        bool ok = true;
        for (int j = 0; j < i; j++) {
            if (areSame(ret[j], ans[i])) {
                ok = false;
                break;
            }
        }
        if (ok) ret.push_back(ans[i]);
    }
    return ret;
}
/*
    Radius of incircle = A / s
    Radius of circumcircle = abc / 4A
    Incentre: intersection of angle bisectors
    Circumcentre: meeting point of perpendicular bisectors
    Cosine Law :- c^2 = a^2 + b^2 - 2 * a * b * cosC
    Sine Law :- a / sinA = b / sinB = c / sinC = 2R(circumradius)
*/
