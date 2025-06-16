struct SEGT {
    int sz = 1;
    vector<int> seg;

    int op(int a, int b) {
        return max(a, b);
    }

    void update(int i, int v, int x, int lx, int rx) {
        if (lx == rx) {
            seg[x] += v;
            return;
        }
        int md = (lx + rx) >> 1;
        if (i <= md) {
            update(i, v, 2 * x + 1, lx, md);
        } else {
            update(i, v, 2 * x + 2, md + 1, rx);
        }
        seg[x] = op(seg[2 * x + 1], seg[2 * x + 2]);
    }

    int query(int l, int r, int x, int lx, int rx) {
        if (r < lx or rx < l) {
            return 0;
        }
        if (l <= lx and rx <= r) {
            return seg[x];
        }
        int mid = (lx + rx) >> 1;
        return op(
        query(l, r, 2 * x + 1, lx, mid), 
        query(l, r, 2 * x + 2, mid + 1, rx)
        );
    }

public:
    SEGT(int n) {
        sz = 1;
        while (sz < n) { sz <<= 1; }
        seg = vector<int>(sz << 1);
    }

    void update(int i, int v) {
        update(i, v, 0, 0, sz - 1);
    }

    int query(int l, int r) {
        return query(l, r, 0, 0, sz - 1);
    }
};
