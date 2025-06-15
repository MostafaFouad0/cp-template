#define ll long long
#define int long long

int const N = 1e5 + 1, M = 1e9 + 7, B = 317;

int n;// n -> number of nodes
vector<vector<int>> adj;//the tree

struct sg {
    vector<int> seg, lazy;
    int sz;

    sg() {}

    sg(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        seg = lazy = vector<int>(sz << 1);
    }

    void propagate(int x, int lx, int rx) {
        if (lx == rx) return;
        if (lazy[x] != 0) {
            lazy[2 * x + 1] += lazy[x];
            lazy[2 * x + 2] += lazy[x];
            seg[2 * x + 1] += lazy[x];
            seg[2 * x + 2] += lazy[x];
        }
        lazy[x] = 0;
    }

    void update(int l, int r, int v, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        propagate(x, lx, rx);
        if (r < lx or rx < l) return;
        if (l <= lx and rx <= r) {
            seg[x] += v;
            lazy[x] += v;
            propagate(x, lx, rx);
            return;
        }
        int md = lx + rx >> 1;
        update(l, r, v, 2 * x + 1, lx, md);
        update(l, r, v, 2 * x + 2, md + 1, rx);
        seg[x] = max(seg[2 * x + 1], seg[2 * x + 2]);
    }

    int query(int l, int r, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        propagate(x, lx, rx);
        if (r < lx or rx < l) return -1e15;
        if (l <= lx and rx <= r) return seg[x];
        int md = lx + rx >> 1;
        return max(query(l, r, 2 * x + 1, lx, md), query(l, r, 2 * x + 2, md + 1, rx));
    }
};

struct HLD {
    vector<int> tp, sz, depth, par, in;
    int timer;
    sg st;

    HLD(int root) {
        tp = sz = depth = par = in = vector<int>(n + 1);
        timer = 0;
        dfs0(root, 0);
        dfs1(root, 0, root);
        st = sg(n + 1);
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

    int query(int u, int v) {
        int ret = LLONG_MIN;
        while (tp[u] != tp[v]) {
            if (depth[tp[u]] < depth[tp[v]]) swap(u, v);
            ret = max(ret, st.query(in[tp[u]], in[u]));
            u = par[tp[u]];
        }

        if (in[u] > in[v]) swap(u, v);
        ret = max(ret, st.query(in[u], in[v]));
        return ret;
    }

    void updatesub(int i, int v) {
        st.update(in[i], in[i] + sz[i] - 1, v);
    }
};

int q;

void dowork() {
    cin >> n;
    adj = vector<vector<int>>(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    HLD hld = HLD(1);
    cin >> q;
    while (q--) {
        string ty;
        int u, v;
        cin >> ty >> u >> v;
        if (ty[0] == 'a') {
            hld.updatesub(u, v);
        } else {
            cout << hld.query(u, v) << '\n';
        }
    }
}
