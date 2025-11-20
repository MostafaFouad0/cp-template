//Mex problem
//Given a tree  and each node have a permutation value p[i]
//type 1 : swap pu, pv
//type 2 : print the largest Mex of any possible path
#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define int long long
#define ll long long
using namespace std;

int const N = 3e5 + 1, LOG = 19, N2 = 1e5 + 1, SQ = 710, M = 1e9 + 7;
vector<vector<int>> adj, st;
vector<int> depth, euler, in, out, lvl;
int timer = 0;
//depth and euler will be 2*n memory and in2 is n
//also st(log, 2*n)

void dfs(int u, int v, int d) {
    in[u] = timer;
    lvl[u] = d;
    euler[timer] = u;
    depth[timer++] = d;
    for (int i: adj[u]) {
        if (i == v) continue;
        dfs(i, u, d + 1);
        euler[timer] = u;
        depth[timer++] = d;
    }
    out[u] = timer;
}

void build_sparse(int n) {
    for (int i = 0; i < n; i++)
        st[0][i] = i;
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            int x = st[k - 1][i];
            int y = st[k - 1][i + (1 << (k - 1))];
            st[k][i] = (depth[x] < depth[y] ? x : y);
        }
    }
}

int lca(int u, int v) {
    int l = in[u], r = in[v];
    if (l > r) swap(l, r);
    int len = r - l + 1;
    int k = __lg(len);
    int x = st[k][l];
    int y = st[k][r - (1 << k) + 1];
    return depth[x] < depth[y] ? euler[x] : euler[y];
}

bool is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

struct sg {
    vector<pair<int, int>> seg;
    int sz;

    sg(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        seg = vector<pair<int, int>>(sz << 1, {0, 0});
    }

    pair<int, int> mrg(pair<int, int> lft, pair<int, int> rgt) {
        if (lft.first == -1 or rgt.first == -1) return {-1, -1};
        if (!lft.first) return rgt;
        if (!rgt.first) return lft;
        vector<int> v = {lft.first, lft.second, rgt.first, rgt.second};
        int a = v[0];
        for (auto i: v) {
            if (lvl[i] > lvl[a]) a = i;
        }
        int b = -1;
        for (auto i: v) {
            if (!is_ancestor(i, a)) {
                if (b == -1) b = i;
                if (lvl[i] > lvl[b]) b = i;
            }
        }
        if (b == -1) {
            b = v[0];
            for (auto i: v) {
                if (lvl[i] < lvl[b]) b = i;
            }
        }
        int lc = lca(a, b);
        for (auto i: v) {
            if (i == a or i == b)continue;
            if (lvl[i] < lvl[lc] || (!is_ancestor(i, a) and !is_ancestor(i, b))) return {-1, -1};
        }
        return {a, b};
    }

    void upd(int i, int v, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        if (lx == rx) {
            seg[x] = {v, v};
            return;
        }
        int md = lx + rx >> 1;
        if (i <= md)upd(i, v, 2 * x + 1, lx, md);
        else upd(i, v, 2 * x + 2, md + 1, rx);
        seg[x] = mrg(seg[2 * x + 1], seg[2 * x + 2]);
    }

    pair<int, int> p;

    int qry(int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1, p = {0, 0};
        if (lx == rx) {
            return lx;
        }
        int md = lx + rx >> 1;
        if (mrg(p, seg[2 * x + 1]).first == -1) {
            return qry(2 * x + 1, lx, md);
        } else {
            p = mrg(p, seg[2 * x + 1]);
            if (~mrg(p, seg[2 * x + 2]).first) return -1;
            else return qry(2 * x + 2, md + 1, rx);
        }
    }
};

int n, q, idx;

void dowork() {
    cin >> n;
    adj = vector<vector<int>>(n + 1);
    depth = euler = vector<int>(2 * n);
    in = out = lvl = vector<int>(n + 1);
    st = vector<vector<int>>(LOG, vector<int>(2 * n));
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    for (int i = 2, u; i <= n; ++i) {
        cin >> u;
        adj[u].emplace_back(i);
        adj[i].emplace_back(u);
    }
    dfs(1, 0, 0);
    build_sparse(2 * n);
    sg tr = sg(n);
    vector<int> pos(n);
    for (int i = 1; i <= n; ++i) {
        pos[p[i]] = i;
        tr.upd(p[i], i);
    }
    cin >> q;
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int u, v;
            cin >> u >> v;
            swap(pos[p[u]], pos[p[v]]);
            tr.upd(p[u], pos[p[u]]);
            tr.upd(p[v], pos[p[v]]);
            swap(p[u], p[v]);
        } else {
            int res = tr.qry();
            cout << (res == -1 ? n : res) << '\n';
        }
    }
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
        ++idx;
        dowork();
        cout << '\n';
    }
}
