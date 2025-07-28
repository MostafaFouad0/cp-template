point reflect(point p, point p0, point p1) {
    point z = p-p0, w = p1-p0;
    return conj(z/w)*w + p0; // Refelect point p1 around p0p1
}

bool isCollinear(point a, point b, point c) {	
	return fabs( cp(b-a, c-a) ) < EPS;	
} 

bool isPointOnRay(point p0, point p1, point p2) {
    if(length(p2-p0) < EPS) return true;
    return same( normalize(p1-p0), normalize(p2-p0) );
}

bool isPointOnRay(point a, point b, point c) {	// not tested?
    if(!isCollinear(a, b, c))
    	return false;
    return dcmp(dp(b-a, c-a), 0) == 1;
}

bool isPointOnSegment(point a, point b, point c) {
	return isPointOnRay(a, b, c) && isPointOnRay(b, a, c);
}

bool isPointOnSegment(point a, point b, point c) {
	double acb = length(a-b), ac = length(a-c), cb = length(b-c);
	return dcmp(acb-(ac+cb), 0) == 0;
}

bool intersectSegments(point a, point b, point c, point d, point & intersect) {
  double d1 = cp(a - b, d - c), d2 = cp(a - c, d - c), d3 = cp(a - b, a - c);
  if (fabs(d1) < EPS)
    return false;  // Parllel || identical

  double t1 = d2 / d1, t2 = d3 / d1;
  intersect = a + (b - a) * t1;

  if (t1 < -EPS || t2 < -EPS || t2 > 1 + EPS)
    return false;  //e.g ab is ray, cd is segment ... change to whatever
  return true;
}


// Where is P2 relative to segment p0-p1?
// ccw = +1 => angle > 0 or collinear after p1
// cw = -1 => angle < 0 or collinear after p0
// Undefined = 0 => Collinar in range [a, b]. Be careful here
int ccw(point a, point b, point c) {
  point v1(b - a), v2(c - a);
  double t = cp(v1, v2);

  if (t > +EPS)
	return +1;
  if (t < -EPS)
	return -1;
  if (v1.X * v2.X < -EPS || v1.Y * v2.Y < -EPS)
	return -1;
  if (norm(v1) < norm(v2) - EPS)
	return +1;
  return 0;
}

  void ccw_testing() {
    point a(0, 0), b(10, 0);

    cout<<ccw(a, b, point(20, 10))<<"\n";     // +1 => c is ccw for a-b
    cout<<ccw(a, b, point(20, 0))<<"\n";      // +1 => Collinear after b

    cout<<ccw(a, b, point(20, -10))<<"\n";    // -1 => c is cw for a-b
    cout<<ccw(a, b, point(-20, 0))<<"\n";     // -1 => c is Collinear before a

    cout<<ccw(a, b, a)<<"\n";               // 0 => Collinear at a
    cout<<ccw(a, b, b)<<"\n";               // 0 => Collinear at b
    cout<<ccw(a, b, (a+b)/2.0)<<"\n";       // 0 => Collinear between a-b

    // one can design ccw to behave little differently
    // e.g. consider Collinear at b = +1 and at a = -1
  }

  bool intersect(point p1, point p2, point p3, point p4) {
    // special case handling if a segment is just a point
    bool x = (p1 == p2), y = (p3==p4);
    if(x && y)  return p1 == p3;
    if(x)   return ccw(p3, p4, p1) == 0;
    if(y)   return ccw(p1, p2, p3) == 0;

    return  ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0  &&
        ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0;
  }

int main() {
  ccw_testing();

  return 0;
}


#define all(v)      ((v).begin()), ((v).end())
#define sz(v)     ((int)((v).size()))
#define clr(v, d)   memset(v, d, sizeof(v))
#define rep(i, v)   for(int i=0;i<sz(v);++i)
#define lp(i, n)    for(int i=0;i<(int)(n);++i)
#define lpi(i, j, n)  for(int i=(j);i<(int)(n);++i)
#define lpd(i, j, n)  for(int i=(j);i>=(int)(n);--i)

int ccw(point a, point b, point c) {
  point v1(b - a), v2(c - a);
  double t = cp(v1, v2);

  if (t > +EPS)
    return +1;
  if (t < -EPS)
    return -1;
  if (v1.X * v2.X < -EPS || v1.Y * v2.Y < -EPS)
    return -1;
  if (norm(v1) < norm(v2) - EPS)
    return +1;
  return 0;
}


bool intersect(point p1, point p2, point p3, point p4) {
  // special case handling if a segment is just a point
  bool x = (p1 == p2), y = (p3==p4);
  if(x && y)  return p1 == p3;
  if(x)   return ccw(p3, p4, p1) == 0;
  if(y)   return ccw(p1, p2, p3) == 0;

  return  ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0  &&
      ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0;
}

////////////////////////////////////////////////////////

// assume p0 is added again to p (n+1 points)
bool isSimplePolygon(vector<point> &p) {
  for (int i = 0; i < sz(p) - 1; i++) {
    for (int j = i + 2; j < sz(p) - 1; j++)
      if (intersect(p[i], p[i + 1], p[j], p[j + 1]) && (i != 0 || j != sz(p) - 2) /* last/first edges are consecutive*/)
        return false;   //Segments must not share vertices
  }
  return true;
}

      bool isConvexPolygon(vector<point> &p) {
        // all polygon 3 consecutive points must have same sign (ccw or cw)
        p.push_back(p[0]), p.push_back(p[1]); // wrap points for simplicity

        int sign = ccw(p[0], p[1], p[2]);
        bool ok = true;
        for (int i = 1; ok && i < sz(p) - 2; i++) {
          if (ccw(p[i], p[i + 1], p[i + 2]) != sign)
            ok = false;
        }
        p.pop_back(), p.pop_back();
        return ok;
      }

      // isConcave = !isConvex
      // isConcave = 2 different signs

// 2 points has infinite circles
// Find circle passes with 3 points, some times, there is no circle! (in case colinear)
// Draw two perpendicular lines and intersect them
// may be see https://www.topcoder.com/community/data-science/data-science-tutorials/geometry-concepts-line-intersection-and-its-applications/
pair<double, point> findCircle(point a, point b, point c) {
	//create median, vector, its prependicular
	point m1 = (b+a)*0.5, v1 = b-a, pv1 = point(v1.Y, -v1.X);
	point m2 = (b+c)*0.5, v2 = b-c, pv2 = point(v2.Y, -v2.X);
	point end1 = m1+pv1, end2 = m2+pv2, center;
	intersectSegments(m1, end1, m2, end2, center);
	return make_pair( length(a-center), center );  
}



// If line intersect cirlce at point p, and p = p0 + t(p1-p0)
// Then (p-c)(p-c) = r^2 substitute p and rearrange
// (p1-p0)(p1-p0)t^2 + 2(p1-p0)(p0-C)t + (p0-C)(p0-C) = r*r; -> Quadratic
vector<point> intersectLineCircle(point p0, point p1, point C, double r) {
    double a = dp(p1-p0, p1-p0), b = 2*dp(p1-p0, p0-C), 
           c = dp(p0-C, p0-C) - r*r;
    double f = b*b - 4*a*c;

    vector<point> v;
    if( dcmp(f, 0) >= 0) {
	    if( dcmp(f, 0) == 0)	f = 0;
	    double t1 =(-b + sqrt(f))/(2*a);
	    double t2 =(-b - sqrt(f))/(2*a);
	    v.push_back( p0 + t1*(p1-p0) );
	    if( dcmp(f, 0) != 0)	v.push_back( p0 + t2*(p1-p0) );
    }
    return v;
}

vector<point> intersectCircleCircle(point c1, double r1, point c2, double r2) {
  // Handle infinity case first: same center/radius and r > 0
  if (same(c1, c2) && dcmp(r1, r2) == 0 && dcmp(r1, 0) > 0)
    return vector<point>(3, c1);    // infinity 2 same circles (not points)

  // Compute 2 intersection case and handle 0, 1, 2 cases
  double ang1 = angle(c2 - c1), ang2 = getAngle_A_abc(r2, r1, length(c2 - c1));

  if(::isnan(ang2)) // if r1 or d = 0 => nan in getAngle_A_abc (/0)
    ang2 = 0; // fix corruption

  vector<point> v(1, polar(r1, ang1 + ang2) + c1);

  // if point NOT on the 2 circles = no intersection
  if(dcmp(dp(v[0]-c1, v[0]-c1), r1*r1) != 0 ||
      dcmp(dp(v[0]-c2, v[0]-c2), r2*r2) != 0 )
    return vector<point>();

  v.push_back(polar(r1, ang1 - ang2) + c1);
  if(same(v[0], v[1]))  // if same, then 1 intersection only
    v.pop_back();
  return v;
}

int intersectCircleCircle_TEST() {
  print(intersectCircleCircle(point(-1.5,-1.5), 0.5, point(1.5,1.5), 0.5));   // no intersection far

  print(intersectCircleCircle(point(0, 0), 5, point(9, 0), 1));   // no intersection far
  print(intersectCircleCircle(point(0, 0), 5, point(0, 0), 1));   // no intersection nested same center
  print(intersectCircleCircle(point(0, 0), 5, point(1, 0), 1));   // no intersection nested

  print(intersectCircleCircle(point(0, 0), 5, point(6, 0), 1));   // 1 intersection: (5,0) external
  print(intersectCircleCircle(point(0, 0), 5, point(4, 0), 1));   // 1 intersection: (5,0) internal
  print(intersectCircleCircle(point(0, 0), 5, point(5, 0), 0));   // 1 intersection: (5,0) point on circle
  print(intersectCircleCircle(point(5, 0), 0, point(5, 0), 0));   // 1 intersection: (5,0) 2 same points

  print(intersectCircleCircle(point(0, 0), 5, point(5, 0), 1));   // 2 intersection: ~(5,1) (5,-1)

  print(intersectCircleCircle(point(0, 0), 5, point(0, 0), 5));   // infinity intersections

  // Full correct testing should consider also swapping these parameters

  return 0;
}



const int MAX = 100000+9;
point pnts[MAX], r[3], cen;
double rad;
int ps, rs;	// ps = n, rs = 0, initially

// Pre condition
// random_shuffle(pnts, pnts+ps);		rs = 0;
void MEC() {
	if(ps == 0 && rs == 2) {
		cen = (r[0]+r[1])/2.0;
		rad = length(r[0]-cen);
	}
	else if(rs == 3) {
		pair<double, point> p = findCircle(r[0], r[1], r[2]);
		cen = p.second;
		rad = p.first;
	}
	else if(ps == 0) {
		cen = r[0];	// sometime be garbage, but will not affect
		rad = 0;
	}
	else {
		ps--;
		MEC();

		if(length(pnts[ps]-cen) > rad) {
			r[rs++] = pnts[ps];
			MEC();
			rs--;
		}

		ps++;
	}
}

double polygonArea(vector<point>& points) {
    long double a = 0;
    rep(i, points)  a += cp(points[i], points[ (i+1) % sz(points) ]);
    return fabs(a/2.0);    // If area > 0 then points ordered ccw
}

point polygonCenteriod(vector<point> points) {
  double x = 0, y = 0, a = 0, c;

  for(int i = 0; i < points.size(): ++i)
  {
	int j = (i + 1) % sz(points);
	c = cp(points[i], points[j]), a += c;
	x += (points[i].X + points[j].X) * c;
	y += (points[i].Y + points[j].Y) * c;
  }
  if (dcmp(a, 0) == 0)
	return (points[0] + points.back()) * 0.5;   // Line
  a /= 2, x /= 6 * a, y /= 6 * a;
  
  // Fix values in case
  if (dcmp(x, 0) == 0)	x = 0;
  if (dcmp(y, 0) == 0)	y = 0;

  return point(x, y);
}


// P need to be counterclockwise convex polygon
pair<vector<point>, vector<point> > polygonCut(vector<point> &p, 
	point A, point B) {
		
  vector<point> left, right;
  point intersect;

  for (int i = 0; i < sz(p); ++i) {
	point cur = p[i], nxt = p[(i + 1) % sz(p)];

	if ( cp(B-A, cur-A) >= 0)
	  right.push_back(cur);

	//NOTE adust intersectSegments should handled AB as line
	if (intersectSegments(A, B, cur, nxt, intersect)) {  
	  right.push_back(intersect);
	  left.push_back(intersect);
	}

	if ( cp(B-A, cur-A) <= 0)
	  left.push_back(cur);
  }
  return make_pair(left, right);
}

#define X real()
#define Y imag()
#define vec(a,b)                ((b)-(a))
#define length(a)               (hypot((a).imag(), (a).real()))

struct cmpX {
  bool operator()(const point &a, const point &b) {
    if (dcmp(a.X, b.X) != 0)
      return dcmp(a.X, b.X) < 0;
    return dcmp(a.Y, b.Y) < 0;
  }
};

struct cmpY {
  bool operator()(const point &a, const point &b) {
    if (dcmp(a.Y, b.Y) != 0)
      return dcmp(a.Y, b.Y) < 0;
    return dcmp(a.X, b.X) < 0;
  }
};

double closestPair1(vector<point> &eventPts) {
  double d = OO;
  multiset<point, cmpY> activeWindow;
  sort(eventPts.begin(), eventPts.end(), cmpX());

  int left = 0;
  for (int right = 0; right < (int) eventPts.size(); ++right) {
    while (left < right && eventPts[right].X - eventPts[left].X > d)
      activeWindow.erase(activeWindow.find(eventPts[left++]));
    auto asIt = activeWindow.lower_bound(point(-OO, eventPts[right].Y - d));
    auto aeIt = activeWindow.upper_bound(point(-OO, eventPts[right].Y + d));
    for (; asIt != aeIt; asIt++)
      d = min(d, length(eventPts[right] - *asIt));
    activeWindow.insert(eventPts[right]);
  }
  return d;
}

int main1() {
#ifndef ONLINE_JUDGE
  freopen("test.txt", "rt", stdin);
#endif

  int n;
  while (cin >> n && n) {
    vector<point> eventPts(n);

    for (int i = 0; i < n; ++i) {
      double x, y;
      cin >> x >> y;
      eventPts[i] = point(x, y);
    }

    double d = closestPair1(eventPts);
  }
  return 0;
}




#define foreach(a,s) for(auto a=(s).begin();a!=(s).end();a++)

double closestPair2(map<double, multiset<double> > & pointsMap) {
  double d = OO;
  foreach(xsIt, pointsMap) foreach(ymIt, xsIt->second) // sweep on each point p
    {
      double x = xsIt->first, y = *ymIt;
      // Iterate on rectangle dx2d (max 6 points)
      // iterate on active set - X dimension (distance d)
      auto xeIt = pointsMap.upper_bound(x + d);
      for (auto xIt = xsIt; xIt != xeIt; xIt++) {
        double x2 = xIt->first;
        // iterate on active set - Y dimension (distance 2d)
        auto ysIt = xIt->second.lower_bound(y - d);
        auto yeIt = xIt->second.upper_bound(y + d);
        for (; ysIt != yeIt; ysIt++) {
          if (xsIt != xIt|| ymIt != ysIt)  // if NOT original (x,y)
            d = min(d, max( abs(x-x2), abs(y-*ysIt)));
        }
      }
    }
  return d;
}

bool isPointOnSegment(point a, point b, point c) {
	double acb = length(a-b), ac = length(a-c), cb = length(b-c);
	return dcmp(acb-(ac+cb), 0) == 0;
}

// Accurate and efficient
int isInsidePoly(vector<point> p, point p0) {
  int wn = 0;  // the winding number counter

  for (int i = 0; i < sz(p); i++) {
	point cur = p[i], nxt = p[(i + 1) % sz(p)];
	if (isPointOnSegment(cur, nxt, p0))
	  return true;
	if (cur.Y <= p0.Y) {    // Upward edge
	  if (nxt.Y > p0.Y && cp(nxt-cur, p0-cur) > EPS)
		++wn;
	} else {                // Downward edge
	  if (nxt.Y <= p0.Y && cp(nxt-cur, p0-cur) < -EPS)
		--wn;
	}
  }
  return wn != 0;
}
