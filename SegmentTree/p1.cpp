// Given an array a of n integers (a1, a2, a3, ..., an).

// For a given l and r, lets define a F function that calculates the maximum integer in the range starting at l and ending at r, in other words F(l, r) = max(al, al + 1, ..., ar - 1, ar).

// You need to perform q queries of the following types:

// type 1) 1 l r: For all l ≤ i ≤ r, set ai:  = F(l, r) - ai.

// type 2) 2 l r: Print the value of F(l, r).

#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define int long long
#define ll long long
using namespace std;

int const N = 1e5 + 1, LOG = 18, N2 = 2e5 + 1, M = 1e9 + 7, SQ = 710, B = 101;

int n, q, idx;
struct Node {
    int val{}, ans = INT_MIN, mn = INT_MAX, flag = 2;
};

int a[N];

struct sg {
    vector<Node> seg;
    int sz;

    sg(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        seg = vector<Node>(sz << 1);
    }

    void build(int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        if (lx == rx) {
            if (lx < n) {
                seg[x].ans = seg[x].mn = a[lx];
            }
            return;
        }
        int md = lx + rx >> 1;
        build(2 * x + 1, lx, md);
        build(2 * x + 2, md + 1, rx);
        seg[x].mn = min(seg[2 * x + 1].mn, seg[2 * x + 2].mn);
        seg[x].ans = max(seg[2 * x + 1].ans, seg[2 * x + 2].ans);
    }

    void apply(int x, int lx, int rx, int v, int flag) {
        if (flag == 0) {
            seg[x].ans = seg[x].ans - v;
            seg[x].mn = seg[x].mn - v;
        } else {
            int c = seg[x].ans;
            seg[x].ans = -seg[x].mn + v;
            seg[x].mn = -c + v;
        }

        if (seg[x].flag == 2) {
            seg[x].val = v;
            seg[x].flag = flag;
        } else if (seg[x].flag == 1) {
            seg[x].val = seg[x].val - v;
            seg[x].flag ^= flag;
        } else {
            seg[x].val = seg[x].val + v;
            seg[x].flag ^= flag;
        }
    }

    void push(int x, int lx, int rx) {
        if (seg[x].flag != 2 && lx != rx) {
            int md = (lx + rx) >> 1;
            apply(2 * x + 1, lx, md, seg[x].val, seg[x].flag);
            apply(2 * x + 2, md + 1, rx, seg[x].val, seg[x].flag);
        }
        seg[x].val = 0;
        seg[x].flag = 2;
    }

    void update(int l, int r, int v, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        push(x, lx, rx);
        if (r < lx or rx < l) return;
        if (l <= lx and rx <= r) {
            apply(x, lx, rx, v, 1);
            push(x, lx, rx);
            return;
        }
        int md = lx + rx >> 1;
        update(l, r, v, 2 * x + 1, lx, md);
        update(l, r, v, 2 * x + 2, md + 1, rx);
        seg[x].mn = min(seg[2 * x + 1].mn, seg[2 * x + 2].mn);
        seg[x].ans = max(seg[2 * x + 1].ans, seg[2 * x + 2].ans);
    }

    int query(int l, int r, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        push(x, lx, rx);
        if (r < lx or rx < l) return INT_MIN;
        if (l <= lx and rx <= r) return seg[x].ans;
        int md = lx + rx >> 1;
        return max(query(l, r, 2 * x + 1, lx, md), query(l, r, 2 * x + 2, md + 1, rx));
    }
};

void dowork() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sg tr = sg(n);
    tr.build();
    while (q--) {
        int ty, l, r;
        cin >> ty >> l >> r;
        --l, --r;
        if (ty == 1) {
            int v = tr.query(l, r);
            tr.update(l, r, v);
        } else {
            cout << tr.query(l, r) << '\n';
        }
    }
}

signed main() {
    Pc_champs
    freopen("rmq.in", "r", stdin);
    int t = 1;
    cin >> t;
    while (t--) {
        ++idx;
        dowork();
        //cout << '\n';
    }
}
