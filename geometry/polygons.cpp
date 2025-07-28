
bool isConvex(vector<point > p) {
    bool hasPos=false, hasNeg=false;
    for (int i=0, n=p.size(); i<n; i++) {
        int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
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
