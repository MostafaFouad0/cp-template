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
