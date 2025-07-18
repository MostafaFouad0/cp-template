//geting the center
vector<int> center(int n, const vector<vector<int>> &adj) {
    vector<int> deg(n + 1);
    queue<int> q;

    for (int i = 1; i <= n; ++i) {
        deg[i] = adj[i].size();
        if (deg[i] <= 1) q.push(i);
    }

    int remaining = n;
    while (remaining > 2) {
        int sz = q.size();
        remaining -= sz;
        for (int i = 0; i < sz; ++i) {
            int u = q.front();
            q.pop();
            for (int v: adj[u]) {
                if (--deg[v] == 1)
                    q.push(v);
            }
        }
    }

    vector<int> centers;
    while (!q.empty()) {
        centers.push_back(q.front());
        q.pop();
    }

    return centers;
}
