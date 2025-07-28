struct line {
    point v;
    T c;

// From direction vector v and offset c
    line(point v, T c) : v(v), c(c) {}

    line(T a, T b, T c) : v{b, -a}, c(c) {}

    line(point p, point q) : v(q - p), c(cross(v, p)) {}

// Will be defined later:
// - these work with T = int
    T side(point p) { return cross(v, p) - c; }

    double dist(point p) { return abs(side(p)) / length(v); }

    double sqDist(point p) { return side(p) * side(p) / (double) lengthSqr(v); }

    line perpThrough(point p) { return {p, p + perp(v)}; }

    bool cmpProj(point p, point q) {
        return dot(v, p) < dot(v, q);
    }

    line translate(point t) { return {v, c + cross(v, t)}; }

    line shiftLeft(double dist) { return {v, c + dist * abs(v)}; }

    point proj(point p) { return p - perp(v) * side(p) / lengthSqr(v); }

    point refl(point p) { return p - perp(v) * 2 * side(p) / lengthSqr(v); }
};

bool inter(line l1, line l2, point  &out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
    return true;
}

line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
    double sign = interior ? 1 : -1;
    return {l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
            l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign};
}

vector<int>lineCanonicalForm(int x,int y,int x2,int y2) {

    int B = -x + x2, A = y - y2, C = -A * x - B * y;
    int g = __gcd(abs(A), __gcd(abs(B), abs(C)));
    B /= g, A /= g, C /= g;
    if (A < 0)
        A *= -1, B *= -1, C *= -1;
    else if (!A && B < 0)
        B *= -1, C *= -1;
    return {A, B, C};
}

bool half(point p) { // true if in blue half
    assert(p.X != 0 || p.Y != 0); // the argument of (0,0) is undefined
    return p.Y > 0 || (p.Y == 0 && p.X < 0);
}

void polarSort(vector<point> &v) {
    sort(v.begin(), v.end(), [](point v, point w) {
        return make_tuple(half(v), 0) <
               make_tuple(half(w), cross(v,w));
    });
}





bool inDisk(point a, point b, point p) {
    return dot(a-p, b-p) <= 0;
}

bool onSegment(point a, point b, point p) {
    return orient(a,b,p) == 0 && inDisk(a,b,p);
}

bool properInter(point a, point b, point c, point d, point &out) {
    double oa = orient(c,d,a),
            ob = orient(c,d,b),
            oc = orient(a,b,c),
            od = orient(a,b,d);

    if (oa*ob < 0 && oc*od < 0) {
        out = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}

struct cmpX {
    bool operator()(point a, point b) {
        return make_pair(a.X, a.Y) < make_pair(b.X, b.Y);
    }
};


set<point,cmpX> inters(point a, point b, point c, point d) {
    point out;
    if (properInter(a, b, c, d, out)) return {out};
    set<point, cmpX> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return s;
}

double segPoint(point a, point b, point p) {
    if (a != b) {
        line l(a,b);
        if (l.cmpProj(a,p) && l.cmpProj(p,b))
            return l.dist(p);
    }
    return min(length(p-a), length(p-b));
}

double segSeg(point a, point b, point c, point d) {
    point dummy;
    if (properInter(a,b,c,d,dummy))
        return 0;
    return min({segPoint(a,b,c), segPoint(a,b,d),
                segPoint(c,d,a), segPoint(c,d,b)});
}

