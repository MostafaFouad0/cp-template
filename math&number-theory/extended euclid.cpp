//ax + by = gcd(a,b),d = gcd(a,b). compute x and y
// there are infinte number of solutions, to get them x = x0 + b/d*k, y= y0 - a/d*k
// ax + by = c is solvable iff c % d == 0
int extended_euclid(int  a, int  b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
