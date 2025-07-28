void solve(int lx, int rx, int l, int r, bool &sign) {
    if (lx > rx) return;
    int md = (lx + rx) >> 1;
    int &ret = dp[sign][md];
    ret = LLONG_MAX;
    int best = -1;
    for (int i = l; i <= min(r, md); ++i) {
        int cost = dp[sign ^ 1][i - 1] + (pre[md] - pre[i - 1]) * (md - i + 1);
        if (cost < ret) best = i, ret = cost;
    }
    //
    //cout << l << '\n';
    solve(lx, md - 1, l, best, sign);
    solve(md + 1, rx, best, r, sign);
}
 
void dowork() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = a[i] + pre[i - 1];
        dp[0][i] = pre[i] * i;
    }
 
    bool sign{};
    for (int i = 1; i < k; ++i) {
        sign ^= 1;
        solve(1 + i, n, 1 + i, n, sign);
    }
 
    cout << dp[sign][n];
}
