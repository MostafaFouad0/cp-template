#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
//#define int long long
#define ll long long
using namespace std;

int const N = 2e5 + 2, LOG = 18, N2 = 1e6 + 1, M = 1e9 + 7, SQ = 710, B = 101;

int n, p, q, timer;
int depth[N], in[N], tree[N], sz[N];
ll ans[N2];
vector<vector<int>> adj;
vector<vector<pair<int, int>>> qu;

struct BIT {
    vector<int> bit;

    BIT() {}

    BIT(int size) {
        bit = vector<int>(size + 1);
    }

    void add(int i, int val) {
        i++;
        while (i < bit.size()) {
            bit[i] += val, i += i & -i;
        }
    }

    int sum(int l, int r) {
        int res = 0;
        r++;
        while (r)res += bit[r], r -= r & -r;
        while (l)res -= bit[l], l -= l & -l;
        return res;
    }
};

BIT bt;

void init(int u, int v) {
    in[u] = timer;
    tree[timer] = u;
    timer++;
    sz[u] = 1;
    for (auto i: adj[u]) {
        if (i == v) continue;
        depth[i] = depth[u] + 1;
        init(i, u);
        sz[u] += sz[i];
    }
}

void add(int node) {
    bt.add(depth[node], 1);
}

void erase(int node) {
    bt.add(depth[node], -1);
}

void dfs(int u, int v, bool keep) {
    int mx = -1, bg = -1;
    for (auto i: adj[u]) {
        if (i == v || sz[i] <= mx) continue;
        mx = sz[i];
        bg = i;
    }

    for (auto i: adj[u]) {
        if (i == v || i == bg) continue;
        dfs(i, u, false);
    }

    if (~bg) dfs(bg, u, true);

    for (auto i: adj[u]) {
        if (i == v || i == bg) continue;
        for (int j = in[i]; j < in[i] + sz[i]; ++j) {
            int node = tree[j];
            for (auto [k, id]: qu[u]) {
                int rem = depth[node] - depth[u];
                int l = depth[u] + max(0, k - rem), r = n;
                if (l <= r) ans[id] += bt.sum(l, r);
            }
        }
        for (int j = in[i]; j < in[i] + sz[i]; ++j) {
            int node = tree[j];
            add(node);
        }
    }

    add(u);
    for (auto [k, id]: qu[u]) {
        int l = depth[u] + k, r = n;
        if (l <= r) ans[id] += bt.sum(l, r);
    }

    if (!keep) {
        for (int i = 0; i < sz[u]; ++i) {
            erase(tree[in[u] + i]);
        }
    }
}

void dowork() {
    cin >> n >> q;
    adj = vector<vector<int>>(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    qu = vector<vector<pair<int, int>>>(n + 1);
    bt = BIT(n + 1);
    init(1, 1);
    for (int i = 0, u, k; i < q; ++i) {
        cin >> u >> k;
        qu[u].emplace_back(k, i);
    }

    dfs(1, 1, 1);

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }
}

signed main() {
    Pc_champs
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        dowork();
        cout << '\n';
    }
}
