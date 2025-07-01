
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
#define perp(a) (point(-(a).Y),(a).X)  //multiply both coordinates  to -1 to get the right prep (clockwise)
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
