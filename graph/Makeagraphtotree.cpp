#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
using namespace std;

#define ll long long
#define int long long

int const N = 5e5 + 2, LOG = 17, N2 = 2 * N + 1, M = 998244353, SQ = 400;

int n, timer, m;
vector<set<int>> adj, adj2;
int dp[N], w[N], cmp[N], low[N], ids[N];
bool on_stack[N];
vector<int> st;

void dfs0(int u) {
    st.push_back(u);
    on_stack[u] = true;
    low[u] = ids[u] = ++timer;
    for (auto j: adj2[u]) {
        if (!ids[j]) dfs0(j);
        if (on_stack[j]) low[u] = min(low[u], low[j]);
    }

    if (ids[u] == low[u]) {
        while (!st.empty()) {
            int node = st.back();
            on_stack[node] = false;
            low[node] = low[u];
            st.pop_back();
            cmp[ids[u]] += w[node];
            if (node == u) break;
        }
    }
}

void dowork() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }

    adj = adj2 = vector<set<int>>(n + 1);
    int u[m], v[m];
    for (int i = 0; i < m; ++i) {
        cin >> u[i] >> v[i];
        adj2[u[i]].insert(v[i]);
    }

    for (int i = 1; i <= n; ++i) {
        if (!ids[i]) dfs0(i);
    }

    for (int i = 0; i < m; ++i) {
        u[i] = low[u[i]];
        v[i] = low[v[i]];
        if (u[i] == v[i]) continue;
        adj[u[i]].insert(v[i]);
    }
}
