//this one if you need the range [l,r] that : 
//fi(x) = ax+b
//res(x) : fl(fl+1(fl+2(...fr(r))))
struct Node {
    int mula, pre, suf;

    Node() : mula(1), pre(0), suf(0) {}

    Node(int a, int b) : mula(a), pre(b), suf(b) {}
};

Node op(Node lft, Node rgt) {
    Node nw = Node();
    nw.mula = (lft.mula * rgt.mula) % M;
    nw.pre = (lft.pre * rgt.mula + rgt.pre) % M;
    nw.suf = (rgt.suf * lft.mula + lft.suf) % M;
    return nw;
}

struct sg {
    vector<Node> seg;
    int sz;

    sg() {}

    sg(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        seg = vector<Node>(sz << 1);
    }

    void update(int i, int a, int b, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        if (lx == rx) {
            seg[x] = Node(a, b);
            return;
        }
        int md = lx + rx >> 1;
        if (i <= md)update(i, a, b, 2 * x + 1, lx, md);
        else update(i, a, b, 2 * x + 2, md + 1, rx);
        seg[x] = op(seg[2 * x + 1], seg[2 * x + 2]);
    }

    Node query(int l, int r, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        if (r < lx or rx < l) return Node();
        if (l <= lx and rx <= r) return seg[x];
        int md = lx + rx >> 1;
        return op(query(l, r, 2 * x + 1, lx, md), query(l, r, 2 * x + 2, md + 1, rx));
    }
};
