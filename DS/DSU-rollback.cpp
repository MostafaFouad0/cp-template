#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
using namespace std;

#define ll long long
//#define int long long

int const N = 1e5 + 5, M = 5e4;
int n, m, k, B;

struct DSU {
    vector<int> par, sz, roll;
    vector<pair<int, int>> update;
    int comp;

    DSU(int size) {
        comp = 0;
        par = sz = vector<int>(size + 1);
        for (int i = 1; i <= size; ++i) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int Findleader(int u) {
        if (par[u] == u) return u;
        return Findleader(par[u]);
    }

    bool merge(int u, int v) {
        u = Findleader(u);
        v = Findleader(v);
        if (u == v) return false;
        comp--;
        if (sz[u] < sz[v]) swap(u, v);
        update.emplace_back(v, u);
        sz[u] += sz[v];
        par[v] = u;
        return true;
    }

    void snap() {
        roll.emplace_back(update.size());
    }

    void undo() {
        if (roll.empty()) return;
        while (roll.back() < (int) update.size()) {
            int u = update.back().first, v = update.back().second;
            update.pop_back();
            sz[v] -= sz[u];
            par[u] = u;
            comp++;
        }
        roll.pop_back();
    }

};

void dowork() {
    cin >> n >> m;
    B = sqrt(m) + 1;
    vector<pair<int, int>> a(m);
    for (auto &[u, v]: a) cin >> u >> v;
    vector<array<int, 3>> queries[B];
    cin >> k;
    vector<int> res(k);
    DSU d = DSU(n);
    d.comp = n;
    for (int i = 0, l, r; i < k; ++i) {
        cin >> l >> r;
        --l, --r;
        if (r - l + 1 > B) {
            queries[l / B].push_back({r, l, i});
            continue;
        }
        d.snap();
        for (int j = l; j <= r; ++j) {
            auto [u, v] = a[j];
            d.merge(u, v);
        }
        res[i] = d.comp;
        d.undo();
    }

    for (int i = 0; i < B; ++i) {
        if (queries[i].empty()) continue;
        sort(queries[i].begin(), queries[i].end());
        int r = (i + 1) * B - 2;
        d.snap();
        for (auto &[rq, lq, iq]: queries[i]) {
            while (r < rq) {
                auto [u, v] = a[++r];
                d.merge(u, v);
            }
            d.snap();
            int l = (i + 1) * B - 1;
            while (lq < l) {
                auto [u, v] = a[--l];
                d.merge(u, v);
            }
            res[iq] = d.comp;
            d.undo();
        }
        d.undo();
    }

    for (auto i: res) cout << i << '\n';
}

signed main() {
    Pc_champs;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    //cin >> t;
    int idx = 1;
    while (t--) {
        dowork();
        cout << "\n";
        idx++;
        //break;
    }
}
