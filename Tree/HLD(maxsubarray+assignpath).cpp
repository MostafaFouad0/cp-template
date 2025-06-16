struct Node {
    int pre, suf, sum, ans;

    Node() : pre(0), suf(0), sum(0), ans(0) {}

    Node(int v) : pre(max(0ll, v)), suf(max(0ll, v)), sum(v), ans(max(0ll, v)) {}
};

Node op(Node lft, Node rgt) {
    Node nw = Node();
    nw.sum = lft.sum + rgt.sum;
    nw.pre = max(lft.pre, lft.sum + rgt.pre);
    nw.suf = max(rgt.suf, rgt.sum + lft.suf);
    nw.ans = max({lft.ans, rgt.ans, lft.suf + rgt.pre});
    return nw;
}

struct sg {
    vector<Node> seg;
    vector<int> lazy;
    int sz;

    sg() {}

    sg(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        seg = vector<Node>(sz << 1);
        lazy = vector<int>(sz << 1, INT_MAX);
    }

    void propagate(int x, int lx, int rx) {
        if (lx == rx) return;
        if (lazy[x] != INT_MAX) {
            int md = lx + rx >> 1;
            int v = max(0ll, lazy[x] * (md - lx + 1));
            seg[2 * x + 1].ans = seg[2 * x + 1].pre = seg[2 * x + 1].suf = v;
            seg[2 * x + 1].sum = lazy[x] * (md - lx + 1);
            v = max(0ll, lazy[x] * (rx - md));
            seg[2 * x + 2].ans = seg[2 * x + 2].pre = seg[2 * x + 2].suf = v;
            seg[2 * x + 2].sum = lazy[x] * (rx - md);
            lazy[2 * x + 1] = lazy[2 * x + 2] = lazy[x];
        }
        lazy[x] = INT_MAX;
    }

    void update(int l, int r, int v, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        propagate(x, lx, rx);
        if (r < lx or rx < l) return;
        if (l <= lx and rx <= r) {
            seg[x] = Node((rx - lx + 1) * v);
            lazy[x] = v;
            propagate(x, lx, rx);
            return;
        }
        int md = lx + rx >> 1;
        update(l, r, v, 2 * x + 1, lx, md);
        update(l, r, v, 2 * x + 2, md + 1, rx);
        seg[x] = op(seg[2 * x + 1], seg[2 * x + 2]);
    }

    Node query(int l, int r, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        propagate(x, lx, rx);
        if (r < lx or rx < l) return Node();
        if (l <= lx and rx <= r) return seg[x];
        int md = lx + rx >> 1;
        return op(query(l, r, 2 * x + 1, lx, md), query(l, r, 2 * x + 2, md + 1, rx));
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
        for (int i = 1; i <= n; ++i) {
            st.update(in[i], in[i], val[i]);
        }
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
        Node lft = Node(), rgt = Node();
        while (tp[u] != tp[v]) {
            if (depth[tp[u]] < depth[tp[v]]) {
                lft = op(st.query(in[tp[v]], in[v]), lft);
                v = par[tp[v]];
            } else {
                rgt = op(st.query(in[tp[u]], in[u]), rgt);
                u = par[tp[u]];
            }
        }

        if (in[u] < in[v]) {
            lft = op(st.query(in[u], in[v]), lft);
        } else {
            rgt = op(st.query(in[v], in[u]), rgt);
        }

        return max({0ll, lft.ans, rgt.ans, lft.pre + rgt.pre});
    }

    void updatepath(int u, int v, int a) {
        while (tp[u] != tp[v]) {
            if (depth[tp[u]] < depth[tp[v]]) swap(u, v);
            st.update(in[tp[u]], in[u], a);
            u = par[tp[u]];
        }

        if (in[u] > in[v]) swap(u, v);
        st.update(in[u], in[v], a);
    }
};
