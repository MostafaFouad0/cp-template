//Given two arrays a, b initially zero

// There is a timer counting, and each second the following happens, they will be given a query, and after they process the query, for each element bi
//  it is set to bi  = bi  + ai. they have two types of queries as following:

// 1 l r x : for each ai such that (l≤i≤r), ai is set to ai = x .
// 2 l r : they should output the sum of all elements bi such that (l≤i≤r).

#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define int long long
#define ll long long
using namespace std;

int const N = 5e5 + 1, LOG = 18, N2 = 2e5 + 1, M = 1e9 + 7, SQ = 710, B = 101;

int n, q, idx;
struct Node1 {
    int val{}, timer{}, sum{};
};

struct Node2 {
    int val, sum{};
};

struct sg {
    vector<Node1> a;
    vector<Node2> b;
    int sz;

    sg(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        a = vector<Node1>(sz << 1);
        b = vector<Node2>(sz << 1);
    }


    void applyb(int x, int lx, int rx, int v) {
        b[x].sum += v * (rx - lx + 1);
        b[x].val += v;
    }

    void push2(int x, int lx, int rx) {
        if (b[x].val and lx != rx) {
            int md = (lx + rx) >> 1;
            applyb(2 * x + 1, lx, md, b[x].val);
            applyb(2 * x + 2, md + 1, rx, b[x].val);
        }
        b[x].val = 0;
    }

    void applya(int x, int lx, int rx, int v, int timer) {
        b[x].sum += a[x].sum * timer;
        if (a[x].val) b[x].val += a[x].val * timer, push2(x, lx, rx);
        a[x].val = v;
        if (!a[x].timer) a[x].timer = timer;
        a[x].sum = v * (rx - lx + 1);
    }

    void push(int x, int lx, int rx) {
        if (a[x].val && lx != rx) {
            int md = (lx + rx) >> 1;
            applya(2 * x + 1, lx, md, a[x].val, a[x].timer);
            applya(2 * x + 2, md + 1, rx, a[x].val, a[x].timer);
        }
        a[x].val = 0, a[x].timer = 0;
    }

    void update(int l, int r, int v, int timer, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        push(x, lx, rx);
        push2(x, lx, rx);
        if (r < lx or rx < l) return;
        if (l <= lx and rx <= r) {
            applya(x, lx, rx, v, timer);
            applyb(x, lx, rx, -(v * timer));
            push2(x, lx, rx);
            push(x, lx, rx);
            return;
        }
        int md = lx + rx >> 1;
        update(l, r, v, timer, 2 * x + 1, lx, md);
        update(l, r, v, timer, 2 * x + 2, md + 1, rx);
        a[x].sum = a[2 * x + 1].sum + a[2 * x + 2].sum;
        b[x].sum = b[2 * x + 1].sum + b[2 * x + 2].sum;
    }

    int query(int l, int r, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        push(x, lx, rx);
        push2(x, lx, rx);
        if (r < lx or rx < l) return 0;
        if (l <= lx and rx <= r) return a[x].sum;
        int md = lx + rx >> 1;
        return query(l, r, 2 * x + 1, lx, md) + query(l, r, 2 * x + 2, md + 1, rx);
    }

    int query2(int l, int r, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = sz - 1;
        push(x, lx, rx);
        push2(x, lx, rx);
        if (r < lx or rx < l) return 0;
        if (l <= lx and rx <= r) return b[x].sum;
        int md = lx + rx >> 1;
        return query2(l, r, 2 * x + 1, lx, md) + query2(l, r, 2 * x + 2, md + 1, rx);
    }
};

void dowork() {
    cin >> n >> q;
    sg tr = sg(n);
    for (int i = 1; i <= q; ++i) {
        int ty, l, r, x;
        cin >> ty >> l >> r;
        --l, --r;
        if (ty == 1) {
            cin >> x;
            tr.update(l, r, x, i);
        } else {
            int v = tr.query(l, r);
            v *= i;
            //cout << tr.query2(l, r) << '\n';
            cout << v + tr.query2(l, r) << '\n';
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
    cin >> t;
    while (t--) {
        ++idx;
        dowork();
        cout << '\n';
    }
}
