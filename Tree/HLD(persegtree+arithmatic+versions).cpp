//problem link:https://www.codechef.com/problems/QUERY
#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
using namespace std;

#define ll long long
#define int long long

int const N = 3e5 + 1, M = 998244353, B = 317;

int n;// n -> number of nodes
vector<vector<int>> adj;//the tree
int L[100 * N], R[100 * N], Sum[100 * N];//100 is logn for newparent + logn*2*2 for propagation
pair<int, int> Lazy[100 * N];

struct persg {
    int ptr;

    persg() {
        ptr = 0;
    }

    int newParent(int l, int r) {
        ptr++;
        L[ptr] = l, R[ptr] = r;
        Sum[ptr] = Sum[l] + Sum[r];
        return ptr;
    }

    int newLazy(int lx, int rx, int node, int a, int b) {
        ptr++;
        L[ptr] = L[node], R[ptr] = R[node];
        Lazy[ptr].first = Lazy[node].first + a;
        Lazy[ptr].second = Lazy[node].second + b;
        int rng = rx - lx + 1;
        Sum[ptr] = Sum[node] + a * rng + b * ((rng * (rng - 1)) / 2);
        return ptr;
    }

    void propagate(int lx, int rx, int node) {
        if (lx == rx) return;
        if (Lazy[node].first or Lazy[node].second) {
            int md = lx + rx >> 1;
            L[node] = newLazy(lx, md, L[node], Lazy[node].first, Lazy[node].second);
            R[node] = newLazy(md + 1, rx, R[node], Lazy[node].first + (md - lx + 1) * Lazy[node].second,
                              Lazy[node].second);
        }
        Lazy[node].first = Lazy[node].second = 0;
    }

    int update(int l, int r, int node, int a, int b, int lx = 0, int rx = n - 1) {
        if (r < lx or rx < l) return node;
        if (l <= lx and rx <= r) return newLazy(lx, rx, node, a + (lx - l) * b, b);
        propagate(lx, rx, node);
        int md = lx + rx >> 1;
        return newParent(update(l, r, L[node], a, b, lx, md), update(l, r, R[node], a, b, md + 1, rx));
    }

    int query(int l, int r, int node, int lx = 0, int rx = n - 1) {
        if (r < lx or rx < l or !node) return 0;
        if (l <= lx and rx <= r) return Sum[node];
        propagate(lx, rx, node);
        int md = lx + rx >> 1;
        return query(l, r, L[node], lx, md) + query(l, r, R[node], md + 1, rx);
    }

};

struct HLD {
    vector<int> tp, sz, depth, par, in;
    int timer;
    persg st;

    HLD(int root) {
        tp = sz = depth = par = in = vector<int>(n + 1);
        timer = 0;
        dfs0(root, 0);
        dfs1(root, 0, root);
        st = persg();
    }

    void dfs0(int u, int v) {
        sz[u] = 1;
        par[u] = v;
        for (auto i: adj[u]) {
            if (i == v) continue;
            depth[i] = depth[u] + 1;
            dfs0(i, u);
            sz[u] += sz[i];
        }
    }

    void dfs1(int u, int v, int top) {
        in[u] = timer++;
        int mx = -1, id = -1;
        tp[u] = top;
        for (auto i: adj[u]) {
            if (i == v) continue;
            if (sz[i] > mx) mx = sz[i], id = i;
        }

        if (!~id) return;
        dfs1(id, u, top);
        for (auto i: adj[u]) {
            if (i == v or id == i) continue;
            dfs1(i, u, i);
        }
    }

    int lca(int u, int v) {
        while (tp[u] != tp[v]) {
            if (depth[tp[u]] < depth[tp[v]])swap(u, v);
            u = par[tp[u]];
        }
        if (depth[u] < depth[v])return u;
        return v;
    }

    int dis(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    //now for query path(u,v) it depend on the data structure it will be used
    //example :
    //sum/Xor-> if update -> bit : else -> prefix
    //gcd/median/>=k/& : if update -> segtree : else -> sparse table

    int query(int u, int v, int version) {
        int ret{};
        while (tp[u] != tp[v]) {
            if (depth[tp[u]] < depth[tp[v]]) {
                ret += st.query(in[tp[v]], in[v], version);
                v = par[tp[v]];
            } else {
                ret += st.query(in[tp[u]], in[u], version);
                u = par[tp[u]];
            }
        }

        if (in[u] > in[v]) swap(u, v);
        ret += st.query(in[u], in[v], version);
        return ret;
    }

    int updatepath(int u, int v, int a, int b, int version) {
        vector<pair<int, int>> lft, rgt;
        while (tp[u] != tp[v]) {
            if (depth[tp[u]] < depth[tp[v]]) {
                rgt.emplace_back(in[tp[v]], in[v]);
                v = par[tp[v]];
            } else {
                lft.emplace_back(in[tp[u]], in[u]);
                u = par[tp[u]];
            }
        }

        int prv{};

        if (in[u] > in[v]) {
            lft.emplace_back(in[v], in[u]);
        } else {
            rgt.emplace_back(in[u], in[v]);
        }

        reverse(rgt.begin(), rgt.end());
        int cur = version;
        for (auto [l, r]: lft) {
            cur = st.update(l, r, cur, a + (prv + (r - l)) * b, -b);
            prv += (r - l + 1);
        }

        for (auto [l, r]: rgt) {
            cur = st.update(l, r, cur, a + prv * b, b);
            prv += (r - l + 1);
        }

        return cur;
    }
};

int q;
vector<int> ver;

void dowork() {
    cin >> n >> q;
    adj = vector<vector<int>>(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    HLD hld = HLD(1);
    int lst{};
    ver.emplace_back(0);
    int cur_ver{};
    while (q--) {
        char ty;
        cin >> ty;
        if (ty == 'c') {
            int u, v, a, b;
            cin >> u >> v >> a >> b;
            u = (u + lst) % n + 1;
            v = (v + lst) % n + 1;
            cur_ver = hld.updatepath(u, v, a, b, cur_ver);
            ver.emplace_back(cur_ver);
        } else if (ty == 'q') {
            int u, v;
            cin >> u >> v;
            u = (u + lst) % n + 1;
            v = (v + lst) % n + 1;
            lst = hld.query(u, v, cur_ver);
            cout << lst << '\n';
        } else {
            int x;
            cin >> x;
            x = (x + lst) % ((int) ver.size());
            cur_ver = ver[x];
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
        dowork();
        //cout << '\n';
    }
}
