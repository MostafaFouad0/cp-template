#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define int long long
#define ll long long
using namespace std;

int const N = 1e3 + 1, LOG = 18, N2 = 1e5 + 1, SQ = 710, M = 1e9 + 7;

int n, q, idx;
vector<int> a, res;
vector<int> lft, rgt;

void solve(int lx, int rx, vector<array<int, 3>> queries) {
    if (queries.empty() or lx > rx) return;
    if (lx == rx) {
        for (auto [_, _1, iq]: queries) res[iq] = a[lx];
        return;
    }
    int md = lx + rx >> 1;
    lft[md] = a[md];
    for (int i = md - 1; i >= lx; --i) {
        lft[i] = min(lft[i + 1], a[i]);
    }
    rgt[md + 1] = a[md + 1];
    for (int i = md + 2; i <= rx; ++i) {
        rgt[i] = min(rgt[i - 1], a[i]);
    }
    vector<array<int, 3>> sp[2];
    for (auto [l, r, iq]: queries) {
        if (l <= md and md <= r) {
            res[iq] = min(lft[l], (md < r ? rgt[r] : INT_MAX));
            continue;
        }
        sp[r > md].push_back({l, r, iq});
    }
    solve(lx, md - 1, sp[0]);
    solve(md + 1, rx, sp[1]);
}

void dowork() {
    cin >> n >> q;
    a = lft = rgt = vector<int>(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    res = vector<int>(q);
    vector<array<int, 3>> queries(q);
    for (int i = 0, l, r; i < q; ++i) {
        cin >> l >> r;
        queries[i] = {l, r, i};
    }
    solve(1, n, queries);
    for (auto i: res) cout << i << '\n';
}
