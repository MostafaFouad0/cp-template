vector<int> tree[N];
int depth[2 * N], euler[2 * N], first[N];
int st[LOG][2 * N];
int timer = 0;

void dfs(int node, int par, int d) {
    first[node] = timer;
    euler[timer] = node;
    depth[timer++] = d;
    for (int child : tree[node]) {
        if (child != par) {
            dfs(child, node, d + 1);
            euler[timer] = node;
            depth[timer++] = d;
        }
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

int get_lca(int u, int v) {
    int l = first[u], r = first[v];
    if (l > r) swap(l, r);
    int len = r - l + 1;
    int k = __lg(len);
    int x = st[k][l];
    int y = st[k][r - (1 << k) + 1];
    return depth[x] < depth[y] ? euler[x] : euler[y];
}
