#define ll long long
#define int long long

int const N = 2e5 + 1, M = 1e9 + 7, B = 317;

int n;// n -> number of nodes
vector<vector<int>> adj;//the tree

struct BIT {
    vector<int> bit;

    BIT(int size) {
        bit = vector<int>(size + 2);
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

int val[N];

struct HLD {
    vector<int> cid, cpos, tp, sz, depth, par;
    vector<vector<int>> chains;

    HLD(int root) {
        cid = vector<int>(n + 1, -1);
        cpos = tp = sz = depth = par = vector<int>(n + 1);
        dfs0(root, 0);
        dfs1(root, 0, root);
        process();
    }

    void dfs0(int u, int v) {
        sz[u] = 1;
        par[u] = v;
        for (auto i: adj[u]) {
            if (i == v) continue;
            depth[i] = depth[u] + 1;
            dfs0(i, u);
            sz[u] += sz[i];
        }
    }

    void dfs1(int u, int v, int top) {
        int mx = -1, id = -1;

        if (!~cid[top]) {
            cid[top] = chains.size();
            chains.emplace_back();
        }

        cpos[u] = chains[cid[top]].size();
        chains[cid[top]].emplace_back(u);
        cid[u] = cid[top];
        tp[u] = top;

        for (auto i: adj[u]) {
            if (i == v) continue;
            if (sz[i] > mx) mx = sz[i], id = i;
        }

        if (!~id) return;
        dfs1(id, u, top);
        for (auto i: adj[u]) {
            if (i == v or id == i) continue;
            dfs1(i, u, i);
        }
    }

    int lca(int u, int v) {
        while (tp[u] != tp[v]) {
            if (depth[tp[u]] < depth[tp[v]])swap(u, v);
            u = par[tp[u]];
        }
        if (depth[u] < depth[v])return u;
        return v;
    }

    int dis(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    //now for query path(u,v) it depend on the data structure it will be used
    //example :
    //sum/Xor-> if update -> bit : else -> prefix
    //gcd/median/>=k/& : if update -> segtree : else -> sparse table

    //process the chains first
    vector<BIT> st;

    void process() {
        for (int i = 0; i < chains.size(); ++i) {
            st.emplace_back(BIT(chains[i].size()));
            for (int j = 0; j < chains[i].size(); ++j) {
                st.back().add(j, val[chains[i][j]]);
            }
        }
    }

    int query(int u, int v) {
        int ret{};
        while (tp[u] != tp[v]) {
            if (depth[tp[u]] < depth[tp[v]]) swap(u, v);
            ret += st[cid[u]].sum(0, cpos[u]);
            u = par[tp[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);
        ret += st[cid[u]].sum(cpos[u], cpos[v]);
        return ret;
    }

    void update(int i, int x) {
        st[cid[i]].add(cpos[i], -val[i]);
        val[i] = x;
        st[cid[i]].add(cpos[i], val[i]);
    }
};

int q;

void dowork() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
    }

    adj = vector<vector<int>>(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    HLD hld = HLD(1);

    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int i, x;
            cin >> i >> x;
            hld.update(i, x);
        } else {
            int u;
            cin >> u;
            cout << hld.query(u, 1) << '\n';
        }
    }
}
