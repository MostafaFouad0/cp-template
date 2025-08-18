// There is an array of n
//  elements, initially filled with zeros. You need to write a data structure that processes three types of queries:

// assign value v to all elements on the segment from l to r−1.
// add v to all elements on the segment from l to r−1.
// find the sum on the segment from l to r−1.

#include <bits/stdc++.h>

using namespace std;
#define int long long
#define endl '\n'

int n, m, sz;

struct segment_tree {

    vector<int> tree, ls, lazy;

    segment_tree(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        lazy = tree = vector<int>(sz << 1);
        ls = vector<int>(sz << 1, -1);
    }


    int add(int a, int b) {
        return a + b;
    }


    void apply(int v, int l, int r, int val, int type) {
        if (ls[v] <= 0) {
            if (type == 1) {
                tree[v] = (r - l + 1) * val;
                lazy[v] = val;
            } else {
                tree[v] += (r - l + 1) * val;
                lazy[v] += val;
            }
            ls[v] = type;
        } else {
            if (type == 0) {
                tree[v] += (r - l + 1) * val;
                lazy[v] += val;
            } else {
                tree[v] = (r - l + 1) * val;
                lazy[v] = val;
            }
        }
    }

    void push(int v, int l, int r) {
        if (ls[v] != -1 && l != r) {
            int md = (l + r) >> 1;
            apply(2 * v + 1, l, md, lazy[v], ls[v]);
            apply(2 * v + 2, md + 1, r, lazy[v], ls[v]);
        }
        ls[v] = -1;
        lazy[v] = 0;
    }

    void update(int l, int r, int val, int t, int v = 0, int vl = 0, int vr = sz - 1) {
        push(v, vl, vr);
        if (l > vr || r < vl) {
            return;
        }
        if (l <= vl && vr <= r) {
            ls[v] = t;
            apply(v, vl, vr, val, t);
            push(v, vl, vr);
            return;
        }
        int mid = (vl + vr) >> 1;
        update(l, r, val, t, v * 2 + 1, vl, mid);
        update(l, r, val, t, v * 2 + 2, mid + 1, vr);
        tree[v] = add(tree[v * 2 + 1], tree[v * 2 + 2]);
    }

    int get(int l, int r, int v = 0, int vl = 0, int vr = sz - 1) {
        push(v, vl, vr);
        if (l > vr || r < vl) {
            return 0;
        }
        if (l <= vl && vr <= r) {
            return tree[v];
        }
        int mid = (vl + vr) >> 1;
        int left = get(l, r, v * 2 + 1, vl, mid);
        int right = get(l, r, v * 2 + 2, mid + 1, vr);
        return add(left, right);
    }
} *sg;

void _go() {
    int l, r, v, t;
    cin >> n >> m;
    sg = new segment_tree(n);
    for (int i = 0; i < m; ++i) {
        cin >> t >> l >> r;
        if (t == 1) {
            cin >> v;
            sg->update(l, --r, v, 1);
        } else if (t == 2) {
            cin >> v;
            sg->update(l, --r, v, 0);
        } else {
            cout << sg->get(l, --r) << endl;
        }
    }
}

signed main() {
    int t = 1;
    //cin >> t;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int testCase = 1; testCase <= t; testCase++) {
        _go();
        // cout << endl;
    }
    return 0;
}
