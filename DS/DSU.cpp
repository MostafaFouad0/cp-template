struct DSU {
    vector<int> par, sz, roll;
    vector<pair<int, int>> update;
    int comp;
 
    DSU() {}
 
    DSU(int size) {// 1-based
        comp = size;
        par = sz = vector<int>(size + 1);
        for (int i = 1; i <= size; ++i) {
            par[i] = i;
            sz[i] = 1;
        }
    }
 
    int Findleader(int u) {
        if (par[u] == u) return u;
        return Findleader(par[u]);
    }
 
    bool merge(int u, int v) {
        u = Findleader(u);
        v = Findleader(v);
        if (u == v) return false;
        comp--;
        if (sz[u] < sz[v]) swap(u, v);
        update.emplace_back(v, u);
        sz[u] += sz[v];
        par[v] = u;
        return true;
    }
 
    void snap() {
        roll.emplace_back(update.size());
    }
 
    void undo() {
        if (roll.empty()) return;
        while (roll.back() < (int) update.size()) {
            int u = update.back().first, v = update.back().second;
            update.pop_back();
            sz[v] -= sz[u];
            par[u] = u;
            comp++;
        }
        roll.pop_back();
    }
 
};
