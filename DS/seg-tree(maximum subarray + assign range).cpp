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
