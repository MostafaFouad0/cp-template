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
