#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
using namespace std;

#define ll long long
//#define int long long

int const N = 1e6 + 5, M = 1e9 + 7;
int n, q, szt, B;

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? (
            (y < hpow) ? 0 : 3
    ) : (
                      (y < hpow) ? 1 : 2
              );
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

//OP2
struct Query {
    int l, r, lca, iq;
    int64_t ord = -1;

    Query() {}

    Query(int _l, int _r, int _lca, int _iq) {
        l = _l, r = _r, lca = _lca, iq = _iq;
        ord = hilbertOrder(l, r, 21, 0);
    }

    bool operator<(Query &other) {
        return ord < other.ord;
    }
};

//OP1
struct Query {
    int l, r, lca, iq;

    Query() {}

    Query(int l, int r, int lca, int iq) : l(l), r(r), lca(lca), iq(iq) {}

    bool operator<(Query &other) {
        if (l / B == other.l / B) return (l / B) & 1 ? r < other.r : r > other.r;
        return l / B < other.l / B;
    }
};

//OP3
struct Query {
    int l, r, lca, iq;

    Query() {}

    Query(int l, int r, int lca, int iq) : l(l), r(r), lca(lca), iq(iq) {}

    bool operator<(Query &other) {
        return make_pair(l / B, r) < make_pair(other.l / B, other.r);
    }
};

void dowork() {
    cin >> n;
    B = sqrt(2 * n) + 1;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    vector<vector<int>> adj(n);
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> in(n), out(n), tree(2 * n), depth(n);
    vector<vector<int>> up(16, vector<int>(n));
    int timer{};
    auto dfs = [&](int u, int v, const auto &self) -> void {
        tree[timer] = u;
        in[u] = timer++;
        for (auto &i: adj[u]) {
            if (i == v) continue;
            depth[i] = depth[u] + 1;
            up[0][i] = u;
            for (int j = 1; j < 16; j++) up[j][i] = up[j - 1][up[j - 1][i]];
            self(i, u, self);
        }
        tree[timer] = u;
        out[u] = timer++;
    };

    dfs(0, 0, dfs);

    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int j = 15; j >= 0; j--) {
            if (diff & (1 << j)) a = up[j][a];
        }
        if (a == b)
            return a;
        for (int j = 15; j >= 0; j--) {
            if (up[j][a] != up[j][b]) {
                a = up[j][a];
                b = up[j][b];
            }
        }
        return up[0][a];
    };

    cin >> q;
    vector<Query> queries(q);
    vector<int> res(q);
    for (int i = 0, u, v; i < q; ++i) {
        char ty;
        cin >> ty >> u >> v;
        --u, --v;
        int lc = lca(u, v);
        if (lc == u) {
            queries[i] = {ty, in[u], in[v], -1, i};
        } else if (lc == v) {
            queries[i] = {ty, in[v], in[u], -1, i};
        } else {
            if (in[u] > in[v]) swap(u, v);
            queries[i] = {ty, out[u], in[v], lc, i};
        }
    }

    vector<bool> vis(n);
    auto add = [&](int i) {
        i = a[i];
        //add node
    };

    auto erase = [&](int i) {
        i = a[i];
        //erase node
    };

    auto update = [&](int i) {
        i = tree[i];
        vis[i] = !vis[i];
        if (vis[i]) add(i);
        else erase(i);
    };

    sort(queries.begin(), queries.end());
    int l = queries[0].l, r = l - 1, current=0;
    for (const auto &[lq, rq, lcaq, iq, ty, _]: queries) {
        while (r < rq) update(++r);
        while (lq < l) update(--l);

        while (rq < r) update(r--);
        while (l < lq) update(l++);

        if (~lcaq) update(in[lcaq]);
        res[iq] = current;
        if (~lcaq) update(in[lcaq]);
    }

    for (auto i: res) cout << i << '\n';
}

signed main() {
    Pc_champs
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
