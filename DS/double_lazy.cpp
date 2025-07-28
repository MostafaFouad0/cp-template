#include <bits/stdc++.h>

using namespace std;

void fileIO(void) {
#ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#endif
#ifdef ONLINE_JUDGE
    freopen("rmq.in", "r", stdin);
#endif
}
void fastIO(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

typedef long long ll;
#define int ll
struct Node
{
    long long mn, mx;
    bool flip;
    int lazy;

    Node() {
        // update this variable to a value that has no effect on the answer of the operation
        mn = 1e18;
        mx = -1e18;
        flip = 0;
        lazy = 0;
    }

    Node(int x) {
        mn = x;
        mx = x;
        flip = 0;
        lazy = 0;
    }

    // write here the logic you want to happen when you add an update query to a node
    void add(int x) {
        mn += x;
        mx += x;

        if(flip)
            lazy -= x;
        else
            lazy += x;
    }

    void minus() {
        int temp = mn;
        mn = -mx;
        mx = -temp;
        flip ^= 1;
    }
};

struct SegTree
{
    int tree_size;
    vector<Node> seg_data;
    SegTree(int n)
    {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        seg_data.resize(2 * tree_size, Node());
    }

    // update this function for the desired operation
    Node merge(Node & lf, Node & ri)
    {
        Node ans = Node();
        ans.mn = min(lf.mn, ri.mn);
        ans.mx = max(lf.mx, ri.mx);
        return ans;
    }

    void init(vector<long long> & nums, int ni, int lx, int rx) {

        if(rx - lx == 1)
        {
            if(lx < nums.size()) {
                seg_data[ni] = Node(nums[lx]);
            }
            return;
        }

        int mid = lx + (rx - lx) / 2;
        init(nums, 2 * ni + 1, lx, mid);
        init(nums, 2 * ni + 2, mid, rx);

        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2 * ni + 2]);
    }

    void init(vector<int> & nums)
    {
        init(nums, 0, 0, tree_size);
    }

    void propagete(int ni, int lx, int rx)
    {
        if(rx - lx == 1 || (seg_data[ni].lazy == 0 && seg_data[ni].flip))
            return;


        if(seg_data[ni].lazy) {
            seg_data[ 2 * ni + 1].add(seg_data[ni].lazy);
            seg_data[ 2 * ni + 2].add(seg_data[ni].lazy);
        }

        if(seg_data[ni].flip) {
            seg_data[ 2 * ni + 1].minus();
            seg_data[ 2 * ni + 2].minus();
        }


        seg_data[ni].flip = 0;
        seg_data[ni].lazy = 0;
    }

    void set(int l, int r, long long value, int node, int lx, int rx)
    {
        propagete(node, lx, rx);

        if(lx >= l && rx <= r)
        {
            seg_data[node].add(value);
            return;
        }
        if(rx <= l || lx >= r)
            return;

        int mid = lx + (rx - lx) / 2;
        set(l, r, value, 2 * node + 1, lx, mid);
        set(l, r, value, 2 * node + 2, mid, rx);

        seg_data[node] = merge(seg_data[2 * node + 1], seg_data[2 * node + 2]);
    }
    void set(int l, int r, long long value) // // zero indexed range and set from l to r-1, i.e [l,r)
    {
        set(l, r, value, 0, 0, tree_size);
    }

    void minus(int l, int r, int node, int lx, int rx)
    {
        propagete(node, lx, rx);

        if(lx >= l && rx <= r)
        {
            seg_data[node].minus();
            return;
        }
        if(rx <= l || lx >= r)
            return;

        int mid = lx + (rx - lx) / 2;
        minus(l, r, 2 * node + 1, lx, mid);
        minus(l, r, 2 * node + 2, mid, rx);

        seg_data[node] = merge(seg_data[2 * node + 1], seg_data[2 * node + 2]);
    }
    void minus(int l, int r) // // zero indexed range and set from l to r-1, i.e [l,r)
    {
        minus(l, r, 0, 0, tree_size);
    }

    Node get_range(int l, int r, int node, int lx, int rx)
    {
        propagete(node, lx, rx);

        if(lx >= l && rx <= r)
            return seg_data[node];
        if(rx <= l || lx >= r)
            return Node();

        int mid = (lx + rx) / 2;

        Node lf = get_range(l, r, 2 * node + 1, lx, mid);
        Node ri = get_range(l, r, 2 * node + 2, mid, rx);
        return merge(lf, ri);
    }

    long long get_range(int l, int r) // zero indexed range and get from l to r-1, i.e [l,r)
    {
        return get_range(l, r, 0, 0, tree_size).mx;
    }
};
void solve(int tc) {

    int n, q; cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegTree st(n);
    st.init(arr);

    while (q--) {
        int op; cin >> op;
        int l, r; cin >> l >> r;
        l--;
        if(op == 1) {
            int mx = st.get_range(l, r);
            st.minus(l, r);
            st.set(l, r, mx);
        }
        else {
            int mx = st.get_range(l, r);
            cout << mx << "\n";
        }
    }

}

signed main() {

    fastIO(); fileIO();
    cout << setprecision(10) << fixed;
    int t = 1; cin >> t;

    for (int i = 1; i <= t; ++i)
        solve(i);

    return 0;
}
