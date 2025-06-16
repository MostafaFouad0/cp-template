// lx=0,rx=-1
int a[N], in[N], out[N], tree[2 * N + 15], freq[N + 1], lvl[N];
bool vis[N];
int dp[26][N];

void dfs(int u, int par)
{
    in[u] = timer++;
    tree[in[u]] = u;
    for (auto it : adj[u])
    {
        if (par != it)
        {
            lvl[it] = lvl[u] + 1;
            dp[0][it] = u;
            dfs(it, u);
        }
    }
    out[u] = timer++;
    tree[out[u]] = u;
}

void build()
{
	// build LCA
    for (int mask = 1; mask < 25; mask++)
    {
        for (int u = 1; u <= n; ++u)
        {
            if (dp[mask - 1][u] != -1)
                dp[mask][u] = dp[mask - 1][dp[mask - 1][u]];
        }
    }
}

int LCA(int u, int v)
{
    if (lvl[u] < lvl[v])swap(u, v);
    int diff = lvl[u] - lvl[v];
    for (int i = 0; diff; i++, diff >>= 1)
    {
        if (diff & 1)
        {
            u = dp[i][u];
        }
    }
    if (u == v)
        return u;
    for (int i = 21; i >= 0; i--)
    {
        int pu = dp[i][u], pv = dp[i][v];
        if (pu != -1 and pv != -1 and pu != pv)
        {
            u = pu, v = pv;
        }
    }
    return dp[0][u];
}

struct MO
{
    int l, r, idx, lca;

    MO()
    {
    }

    MO(int u, int v, int idx)
    {
        this->idx = idx;
        if (in[u] > in[v])swap(u, v);
        lca = LCA(u, v);
        if (lca == u)
        {
            l = in[u], r = in[v], lca = -1;
        }
        else
        {
            l = out[u], r = in[v];
        }
    }

    bool operator<(const MO& rhs) const
    {
        if (this->l / SQT != rhs.l / SQT)return this->l / SQT < rhs.l / SQT;
        return this->r < rhs.r;
    }
};


void add(int u)
{
		// u is the node number
    if (++freq[a[u]] == 1)cnt++;
}

void del(int u)
{
		// u is the node number
    if (--freq[a[u]] == 0)cnt--;
}

void query(int u)
{
    u = tree[u];
    vis[u] ^= 1;
    if (vis[u])add(u);
    else del(u);
}
/// the code below should be placed inside of the solve function
void solve(){
		dfs(1, 0);
    build();
    vector<MO> queries(q);
    vector<int> ans(q);
    for (int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        queries[i] = MO(u, v, i);
    }
    sort(queries.begin(), queries.end());
    for (auto& [l,r,idx,lca] : queries)
    {
        while (lx > l)query(--lx);
        while (rx < r)query(++rx);
        while (rx > r)query(rx--);
        while (lx < l)query(lx++);
        if (lca != -1)add(lca);
        ans[idx] = cnt;
        if (lca != -1)del(lca);
    }
    for (auto it : ans)cout << it << "\n";
}
