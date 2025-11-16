vector<vector<int>> adj, st;
vector<int> depth, euler, in;
int timer = 0;
//depth and euler will be 2*n memory and in is n
//also st(log, 2*n)

void dfs(int u, int v, int d) {
    in[u] = timer;
    euler[timer] = u;
    depth[timer++] = d;
    for (int i: adj[u]) {
        if (i == v) continue;
        dfs(i, u, d + 1);
        euler[timer] = u;
        depth[timer++] = d;
    }
}

void build_sparse(int n) {
    for (int i = 0; i < n; i++)
        st[0][i] = i;
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            int x = st[k - 1][i];
            int y = st[k - 1][i + (1 << (k - 1))];
            st[k][i] = (depth[x] < depth[y] ? x : y);
        }
    }
}

int lca(int u, int v) {
    int l = in[u], r = in[v];
    if (l > r) swap(l, r);
    int len = r - l + 1;
    int k = __lg(len);
    int x = st[k][l];
    int y = st[k][r - (1 << k) + 1];
    return depth[x] < depth[y] ? euler[x] : euler[y];
}
