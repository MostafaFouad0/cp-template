int ternary_search(int l, int r) {
    while (l <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        int f1 = f(m1);      //evaluates the function at m1
        int f2 = f(m2);      //evaluates the function at m2
        if (f1 < f2)
            l = m1 + 1;
        else
            r = m2 - 1;
    }
    return f(l);                    //return the maximum of f(x) in [l, r]
}
