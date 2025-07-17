pair<int, int> val[N];

void dfs0(int u, int v, vector<vector<int>> &adj) {
    vector<pair<int, int>> ch;
    vector<int> tmp;
    int sz = 2;
    for (auto i: adj[u]) {
        if (i == v) continue;
        tmp.emplace_back(dfs0(i, u, adj));
        sz += tmp.back();
        ch.emplace_back(val[i].first, val[i].second);
    }

    int sz2 = sz;

    pair<int, int> ret = {fast_power(B, sz, M), fast_power(B2, sz, M2)};
    sz--;
    int j{};
    for (auto [f, s]: ch) {
        sz -= tmp[j];
        ret.first += (f * fast_power(B, sz, M)) % M;
        ret.first %= M;
        ret.second += (s * fast_power(B2, sz, M)) % M2;
        ret.second %= M2;
        j++;
    }

    ret.first = (ret.first + 2) % M;
    ret.second = (ret.second + 2) % M2;
    val[u] = ret;
    return sz2;
}
