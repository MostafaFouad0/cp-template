//only need two things to know about
//if a value will be added to segment : what the result if there was a value first in this node ? how to handle when it push down to there childs!

struct Node {
    //
};

struct sg {
    vector<Node> seg;
    int sz;

    sg(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        seg = vector<Node>(sz << 1);
    }

    void apply(int x, int lx, int rx, int v) {
        //apply operation
    }

    void push(int x, int lx, int rx) {
        if (seg[x].lazy && lx != rx) {
            int md = (lx + rx) >> 1;
            apply(2 * x + 1, lx, md, seg[x].lazy);
            apply(2 * x + 2, md + 1, rx, seg[x].lazy);
        }
        //return the lazy to -1
    }

    void update(int l, int r, int v, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        push(x, lx, rx);
        if (r < lx or rx < l) return;
        if (l <= lx and rx <= r) {
            apply(x, lx, rx, v);
            push(x, lx, rx);
            return;
        }
        int md = lx + rx >> 1;
        update(l, r, v, 2 * x + 1, lx, md);
        update(l, r, v, 2 * x + 2, md + 1, rx);
    }

    int query(int l, int r, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        push(x, lx, rx);
        if (r < lx or rx < l) return //;
        if (l <= lx and rx <= r) return //;
        int md = lx + rx >> 1;
        return //(query(l, r, 2 * x + 1, lx, md), query(l, r, 2 * x + 2, md + 1, rx));
    }
};
