#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
using namespace std;

#define ll long long
#define int long long

int const N = 1e5 + 1, LOG = 17, N2 = 3e5 + 5;
int n, m;
int const dx[] = {0, 0, -1, 1, -1, 1, -1, 1};
int const dy[] = {1, -1, 0, 0, -1, 1, 1, -1};
int dp[2][N], a[N];
int frq[N];
int current, lq, rq;

void add(int i) {
    i = a[i];
    current += frq[i];
    frq[i]++;
}

void erase(int i) {
    i = a[i];
    frq[i]--;
    current -= frq[i];
}

void update(int l, int r) {
    while (rq < r) add(++rq);
    while (l < lq) add(--lq);
    while (r < rq) erase(rq--);
    while (lq < l) erase(lq++);
}

void solve(int lx, int rx, int l, int r, bool &sign) {
    if (lx > rx) return;
    int md = (lx + rx) >> 1;
    int &ret = dp[sign][md];
    ret = LLONG_MAX;
    int best = -1;
    for (int i = min(md, r); i >= l; --i) {
        update(i, md);
        if (ret > current + dp[sign ^ 1][i - 1]) ret = current + dp[sign ^ 1][i - 1], best = i;
    }
    solve(lx, md - 1, l, best, sign);
    solve(md + 1, rx, best, r, sign);
}

void dowork() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        dp[0][i] = 1e12;
    }
    lq = 1, rq = 0;
    bool sign{};
    for (int i = 0; i < m; ++i) {
        sign ^= 1;
        solve(1 + i, n, 1 + i, n, sign);
    }

    cout << dp[sign][n];
}


signed main() {
    Pc_champs
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        dowork();
        //cout << "\n";
    }
}
