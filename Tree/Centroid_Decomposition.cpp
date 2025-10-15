vector<vector<int>> adj;
vector<int> sub;
vector<bool> removed;

int get_size(int u, int v = -1) {
    sub[u] = 1;
    for (auto i: adj[u]) {
        if (i == v) continue;
        sub[u] += get_size(i, u);
    }
    return sub[u];
}

int get_centroid(int u, int sz, int v = -1) {
    for (auto i: adj[u]) {
        if (i == v or removed[i]) continue;
        if (sub[i] * 2 > sz) get_centroid(i, sz, u);
    }
    return u;
}

void build_centroid(int u) {
    int centroid = get_centroid(u, get_size(u));
    removed[centroid] = true;
    for (auto i: adj[centroid]) {
        if (removed[i]) continue;
        //the function will be here.
    }
    for (auto i: adj[centroid]) {
        if (removed[i]) continue;
        build_centroid(i);
    }
}
