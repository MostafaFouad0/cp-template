#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define int long long
#define ll long long
using namespace std;

int const N = 1e5 + 1, LOG = 18, N2 = 1e5 + 1, SQ = 710, M = 1e9 + 7;

int n, m, idx;
vector<vector<int>> adj, scc, adj2;
vector<int> in, comp;
vector<bool> vis;

void dfs_in(int u) {
    vis[u] = true;
    for (auto i: adj[u]) {
        if (!vis[i])dfs_in(i);
    }
    in.emplace_back(u);
}

void dfs_out(int u) {
    vis[u] = true;
    for (auto i: adj2[u]) {
        if (!vis[i])dfs_out(i);
    }
    comp.emplace_back(u);
}

void dowork() {
    cin >> n >> m;
    adj = adj2 = vector<vector<int>>(n);
    in = vector<int>(n);
    vis = vector<bool>(n);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj2[v].emplace_back(u);
    }

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs_in(i);
    }

    reverse(in.begin(), in.end());
    vis = vector<bool>(n);

    for (int i = 0; i < n; ++i) {
        if (!vis[in[i]]) {
            dfs_out(in[i]);
            scc.push_back(comp);
            comp.clear();
        }
    }

    cout << scc.size() << '\n';
    for (auto v: scc) {
        cout << v.size() << ' ';
        for (auto i: v) cout << i << ' ';
        cout << '\n';
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
        ++idx;
        dowork();
        cout << '\n';
    }
}
