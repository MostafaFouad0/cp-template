https://cp-algorithms.com/num_methods/ternary_search.html
newtons method 
https://www.google.com/search?q=dp+convex+hull+trick&oq=dp+oncvex&gs_lcrp=EgZjaHJvbWUqCQgBEAAYDRiABDIGCAAQRRg5MgkIARAAGA0YgAQyDQgCEAAYhgMYgAQYigUyDQgDEAAYhgMYgAQYigUyDQgEEAAYhgMYgAQYigUyDQgFEAAYhgMYgAQYigUyDQgGEAAYhgMYgAQYigUyCggHEAAYgAQYogQyCggIEAAYgAQYogQyCggJEAAYgAQYogTSAQg0NjMwajBqN6gCALACAA&sourceid=chrome&ie=UTF-8

https://www.youtube.com/watch?v=Z-1Z-1utYuI&list=PLPt2dINI2MIZcJ3kADyFAOKOwzuvT-g7P&index=7
line sweep
x*(ld) + (ld)

hypot(x,y) :The square root of (x2+y2), more precise and less error 
atan2(y,x) :calculate theta 
exp(p) : if p is a point then the result is e^p even if p is a complex number  

typedef ld T;
typedef complex<T> point;
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define polar(r,t) ((r)*exp(point(0,(t)))) //r = length, t = theta
#define angle(v) atan2(((v).Y),((v).X))  // -pi to pi
#define length(v) hypot((long double)((v).X),((v).Y))
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())
#define lengthSqr(v) (dot((v),(v)))
#define rotate(v,t) (polar(v,t)) //v is a vector rotated , t is theta
#define rotateabout (v,t,a) (rotate(vec(a,v),t)+(a))  // a is new origin, vector rotated around new origin a
#define reflect(p,m) ((conj((p)/(m)))*(m)) //m is mirror
#define normalize(p) ((p)/length(p))
#define same(a,b) (lengthsSqr(vec(a,b)))<EPS)
#define mid(a,b) (((a)+(b))/point(2,0))
#define perp(a) (point(-(a).Y,(a).X))  //multiply both coordinates  to -1 to get the right prep (clockwise)
#define scale(c,factor ,p) ((c)+factor((p)-(c)))


bool isPerp(point v, point w) {return dot(v,w) == 0;}


double fixAngle(long double angle) {
    return angle > 1 ? 1 : (angle < -1 ? -1 : angle);
}


double angleBetween(point p1,point p2) {
    return acos(fixAngle(dot(p1, p2) / length(p1) / length(p2)));
}

T orient(point a, point b, point c) {return cross(b-a,c-a);}

bool inAngle(point a, point b, point c, point p) {
   assert(orient(a,b,c) != 0);
   if (orient(a,b,c) < 0) swap(b,c);
   return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}

long double orientedAngle(point  a, point b, point c) {

 /*the amplitude of an oriented angle\BAC, that is, 
the angle that is covered if we turn from B to C around A counterclockwise.*/

    if (orient(a, b, c) >= 0)
        return angleBetween(b - a, c - a);
    else
        return 2.0 * PI - angleBetween(b - a, c - a);
}

bool isConvex(vector<point > p) {
    bool hasPos=false, hasNeg=false;
    for (int i=0, n=p.size(); i<n; i++) {
        int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
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
    return min(abs(p-a), abs(p-b));
}

double segSeg(point a, point b, point c, point d) {
    point dummy;
    if (properInter(a,b,c,d,dummy))
        return 0;
    return min({segPoint(a,b,c), segPoint(a,b,d),
                segPoint(c,d,a), segPoint(c,d,b)});
}

double areaTriangle(point a, point b, point c) {
    return abs(cross(b-a, c-a)) / 2.0;
}

double areaPolygon(vector<point> p) {
    double area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i+1)%n]);
    }
    return abs(area) / 2.0;
}
bool above(point a, point p) {
    return p.Y >= a.Y;
}

bool crossesRay(point a, point p, point q) {
    return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;
}

bool inPolygon(vector<point> p, point a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i+1)%n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
    }
    return numCrossings & 1; 
}
point circumCenter(point a, point b, point c) {
    b = b-a, c = c-a;
    assert(cross(b,c) != 0);
    return a + perp(b*lengthSqr(c) - c*lengthSqr(b))/cross(b,c)/2;
}

int circleLine(point o, double r, line l, pair<point,point> &out) {
    double h2 = r * r - l.sqDist(o);
    if (h2 >= 0) {
        point p = l.proj(o);
        point h = l.v * sqrt(h2) / abs(l.v);
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}

int circleCircle(point o1, double r1, point o2, double r2, pair<point,point> &out) {
    point d=o2-o1; double d2=lengthSqr(d);
    if (d2 == 0) {assert(r1 != r2); return 0;}
    double pd = (d2 + r1*r1 - r2*r2)/2;
    double h2 = r1*r1 - pd*pd/d2;
    if (h2 >= 0) {
        point p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

// circle circle intersection area 

    int x1, y1, r1, x2, y2, r2;
    int d = r1 + r2, d2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    d *= d;
    //cout << d << " " << d2 << " " << abs(r1 - r2) * abs(r1 - r2) << endl;
    if (d2 >= d)cout << 0;
    else if (d2 == abs(r1 - r2) * abs(r1 - r2)) {
        cout << fixed << setprecision(10) << PI * abs(r1 * r1 - r2 * r2);
    } else if (d2 < abs(r1 - r2) * abs(r1 - r2))cout << 0;
    else {
        ld len = sqrt(d2);
        ld theta1 = 2.0 * acos((d2 + r1 * r1 - r2 * r2) / ((ld) r1 * len * 2.0));
        ld an1 = 0.5 * r1 * r1 * (theta1 - sin(theta1));
        ld theta2 = 2.0 * acos((d2 + r2 * r2 - r1 * r1) / ((ld) r2 * len * 2.0));
        ld an2 = 0.5 * r2 * r2 * (theta2 - sin(theta2));
        //cout << fixed << setprecision(10) << theta1 << " " << theta2 << endl;
        an1 += an2;
        cout << fixed << setprecision(10) << an1 + an2;
    }

int dcmp(double a,double b) {
    return fabs(a - b) <= EPS ? 0 : a > b ? 1 : -1;
}

struct angleCmp {
    point center;
    angleCmp(point a) {
        center = a;
    }
    bool operator()(const point &p1, const point p2) {
        if (!dcmp(cross(p1 - center, p2 - center), 0)) {
            if (fabs(p1.Y - p2.Y) <= EPS)
                return p1.X < p2.X;
            return p1.Y < p2.Y;
        }
        return cross(p1 - center, p2 - center) < 0;
    }
};

vector<point> ConvexHull(vector<point> points) {
    if (points.size() <= 1) return points;

    for (int i = 0; i < points.size(); i++)
        if (make_pair(points[i].Y, points[i].X) < make_pair(points[0].Y, points[0].X))
            swap(points[0], points[i]);

    sort(points.begin() + 1, points.end(), angleCmp(points[0]));

    vector<point> p, ch;

/*
    //To remove co-linear points, un-comment this part
    for (int i = 0; i < points.size(); i++) {
        if (p.size() > 1 && !cross(p.back() - p[0], points[i] - p[0])) {
            if (abs(points[0] - p.back()) < abs(points[0] - points[i]))
                p.back() = points[i];
        } else
            p.push_back(points[i]);
    }
    points = p;
*/

    for (auto point: points) {
        while (ch.size() > 1 &&
               cross(ch[(int) ch.size() - 2] - ch[(int) ch.size() - 1], point - ch[(int) ch.size() - 1]) < 0)
            ch.pop_back();
        ch.push_back(point);
    }
 
    return ch;
}

// rotating calipers
// the convex must have at least 3 points
#define nx(i) (i+1)%n
#define pv(i) (i-1+n)%n

int sign(ll num) {
    if (num < 0) return -1;
    else if (num == 0) return 0;
    else return 1;
}

vector<pair<int,int>> all_anti_podal(int n, vector<point> &p) {
    int p1 = 0, p2 = 0; // two "pointers"
    vector<pair<int,int>> result;

    // parallel edges should't be visited twice
    vector<bool> vis(n, false);

    for (;p1<n;p1++) {
        // the edge that we are going to consider in this iteration
        // the datatype is Point, but it acts as a vector
        point base = p[nx(p1)] - p[p1];

        // the last condition makes sure that the cross products don't have the same sign
        while (p2 == p1 || p2 == nx(p1) || sign(cross(base, p[nx(p2)] - p[p2])) == sign(cross(base, p[p2] - p[pv(p2)]))) {
            p2 = nx(p2);
        }

        if (vis[p1]) continue;
        vis[p1] = true;

        result.push_back({p1, p2});
        result.push_back({nx(p1), p2});

        // if both edges from p1 and p2 are parallel to each other
        if (cross(base, p[nx(p2)] - p[p2]) == 0) {
            result.push_back({p1, nx(p2)});
            result.push_back({nx(p1), nx(p2)});
            vis[p2] = true;
        }
    }

    return result;
}

//half plane intersection 

const long double eps = 1e-9, inf = 1e9;
struct Halfplane {

    // 'p' is a passing point of the line and 'pq' is the direction vector of the line.
    point p, pq;
    long double angle;

    Halfplane() {}
    Halfplane(const point& a, const point& b) : p(a), pq(b - a) {
        angle = atan2l(pq.Y, pq.X);
    }

    // Check if point 'r' is outside this half-plane.
    // Every half-plane allows the region to the LEFT of its line.
    bool out(const point& r) {
        return cross(pq, r - p) < -EPS;
    }

    // Comparator for sorting.
    bool operator < (const Halfplane& e) const {
        return angle < e.angle;
    }

    // Intersection point of the lines of two half-planes. It is assumed they're never parallel.
    friend point inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
        return s.p + (s.pq * alpha);
    }
};

vector<point> hp_intersect(vector<Halfplane>& H) {

    point box[4] = {  // Bounding box in CCW order
            point(inf, inf),
            point(-inf, inf),
            point(-inf, -inf),
            point(inf, -inf)
    };

    for(int i = 0; i<4; i++) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    // Sort by angle and start algorithm
    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < (int)H.size(); i++) {

        // Remove from the back of the deque while last half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        // Remove from the front of the deque while first half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        // Special case check: Parallel half-planes
        if (len > 0 && fabsl(cross(H[i].pq, dq[len-1].pq)) < EPS) {
            // Opposite parallel half-planes that ended up checked against each other.
            if (dot(H[i].pq, dq[len-1].pq) < 0.0)
                return vector<point>();

            // Same direction half-plane: keep only the leftmost half-plane.
            if (H[i].out(dq[len-1].p)) {
                dq.pop_back();
                --len;
            }
            else continue;
        }

        // Add new half-plane
        dq.push_back(H[i]);
        ++len;
    }

    // Final cleanup: Check half-planes at the front against the back and vice-versa
    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    // Report empty intersection if necessary
    if (len < 3) return vector<point>();

    // Reconstruct the convex polygon from the remaining half-planes.
    vector<point> ret(len);
    for(int i = 0; i+1 < len; i++) {
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}
