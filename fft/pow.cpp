vector<int> poly_pow(vector<int> poly, int p, int limit = 1e6+5) {
    vector<int> ans{1};
    while (p) {
        if (p & 1) ans = multiply(ans, poly);
        poly = multiply(poly, poly);
        if (ans.size() > limit)ans.resize(limit + 1);
        if (poly.size() > limit) poly.resize(limit + 1);
        p >>= 1;
    }
    return ans;
}
