void dfs(int u, int par)
{
    for (auto it : adj[u])
    {
        if (par != it)
        {
            lvl[it] = lvl[u] + 1;
            dp[0][it] = u;
            dfs(it, u);
        }
    }
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
