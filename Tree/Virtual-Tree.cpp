//given a distinct n nodes and want to calculate any thing about them only use this -- it include only the important nodes you actually need!
//build_vr return root of this tree
//remember to clear adj2 !!
vector<vector<int>> adj, st;
vector<int> depth, euler, in, out;
int timer = 0;

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
    out[u] = timer;
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
vector<vector<int>> adj2;

bool is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

bool cmp(int u, int v) {
    return in[u] < in[v];
}

int build_vr(vector<int> vr_nodes) {
    sort(vr_nodes.begin(), vr_nodes.end(), cmp);
    int sz = vr_nodes.size();
    for (int i = 0; i < sz - 1; ++i) {
        vr_nodes.push_back(lca(vr_nodes[i], vr_nodes[i + 1]));
    }
    sort(vr_nodes.begin(), vr_nodes.end(), cmp);
    vr_nodes.erase(unique(vr_nodes.begin(), vr_nodes.end()), vr_nodes.end());

    sz = vr_nodes.size();
    for (int i = 0; i < sz; ++i) adj2[vr_nodes[i]].clear();

    vector<int> v{vr_nodes[0]};
    for (int i = 1; i < sz; ++i) {
        int u = vr_nodes[i];
        while (v.size() >= 2 && !is_ancestor(v.back(), u)) {
            adj2[v[v.size() - 2]].push_back(v.back());
            v.pop_back();
        }
        v.push_back(u);
    }

    while (v.size() >= 2) {
        adj2[v[v.size() - 2]].push_back(v.back());
        v.pop_back();
    }
    return vr_nodes[0];
}
