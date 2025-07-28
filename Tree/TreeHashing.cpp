//N -> size of array
ll base1 = 31, base2 = 37, pw1[N + 1], pw2[N + 1];
pii pre[27][N + 1];
void init() {
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i < 27; ++i) {
        pre[i][1].first = i;
        pre[i][1].second = i;
    }
    for (int i = 1; i < N; i++) {
        pw1[i] = (base1 * pw1[i - 1]) % M1;
        pw2[i] = (base2 * pw2[i - 1]) % M2;
        if (i > 1) {
            for (int j = 1; j < 27; ++j) {
                pre[j][i].first = (pre[j][i - 1].first * base1 + j) % M1;
                pre[j][i].second = (pre[j][i - 1].second * base2 + j) % M2;
            }
        }
    }
}

struct Tree {
    vector<pii > seg;
    vector<int> lazy;

    Tree() {
        sz = 1;
        while (sz < n) sz <<= 1;
        seg = vector<pii >(sz << 1);
        lazy = vector<int>(sz << 1, -1);
    }

    pii merge(pii l, pii r, int len) {
        pii res = l;
        res.F = res.F * pw1[len] % M1;
        res.S = res.S * pw2[len] % M2;
        res.F = (res.F + r.F) % M1;
        res.S = (res.S + r.S) % M2;
        return res;
    }

    void apply(int x, int val, int len) {
        seg[x].first = pre[val][len].first;
        seg[x].second = pre[val][len].second;
    }

    void propagate(int x, int lx, int rx) {
        if (lazy[x] == -1) return;
        if (rx != lx) {
            int mid = (lx + rx) >> 1;
            apply(2 * x + 1, lazy[x], mid - lx + 1);
            apply(2 * x + 2, lazy[x], rx - mid);
            lazy[2 * x + 1] = lazy[x];
            lazy[2 * x + 2] = lazy[x];
        }
        lazy[x] = -1;
    }

    void update(int l, int r, int val, int x = 0, int lx = 0, int rx = sz - 1) {
        propagate(x, lx, rx);
        if (lx > r || l > rx) return;
        if (lx >= l && rx <= r) {
            apply(x, val, rx - lx + 1);
            lazy[x] = val;
            return;
        }
        int mid = (lx + rx) >> 1;
        update(l, r, val, 2 * x + 1, lx, mid);
        update(l, r, val, 2 * x + 2, mid + 1, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2], rx - mid);
    }

    piii query(int l, int r, int x = 0, int lx = 0, int rx = sz - 1) {
        propagate(x, lx, rx);
        if (l <= lx && rx <= r) return {seg[x], rx - lx + 1};
        if (l > rx || r < lx) return {{0, 0}, 0};
        int mid = (lx + rx) >> 1;
        auto lft = query(l, r, 2 * x + 1, lx, mid);
        auto rgt = query(l, r, 2 * x + 2, mid + 1, rx);
        auto res = merge(lft.F, rgt.F, rgt.S);
        return {res, lft.S + rgt.S};
    }
};
