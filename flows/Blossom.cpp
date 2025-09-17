//given a graph with n vertices and m edges .. find the maximum matching !
//O(n^3)
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Blossom {
    vector<int> vis, par, orig, match, aux;
    int n, t;
    vector<vector<int>> g;
    queue<int> Q;

    Blossom() {}

    Blossom(int _n) {
        n = _n;
        t = 0;
        for (int i = 0; i <= _n; ++i) {
            g = vector<vector<int>>(_n + 1);
            vis = par = orig = match = aux = vector<int>(_n + 1);
        }
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void augment(int u, int v) {
        int pv = v, nv;
        do {
            pv = par[v];
            nv = match[pv];
            match[v] = pv;
            match[pv] = v;
            v = nv;
        } while (u != pv);
    }

    int lca(int v, int w) {
        ++t;
        while (true) {
            if (v) {
                if (aux[v] == t) return v;
                aux[v] = t;
                v = orig[par[match[v]]];
            }
            swap(v, w);
        }
    }

    void blossom(int v, int w, int a) {
        while (orig[v] != a) {
            par[v] = w;
            w = match[v];
            if (vis[w] == 1) Q.push(w), vis[w] = 0;
            orig[v] = orig[w] = a;
            v = par[w];
        }
    }

    //it finds an augmented path starting from u
    bool bfs(int u) {
        vis = vector<int>(n + 1, -1);
        orig = vector<int>(n + 1, 1);
        Q = queue<int>();
        Q.push(u);
        vis[u] = 0;
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int x: g[v]) {
                if (vis[x] == -1) {
                    par[x] = v;
                    vis[x] = 1;
                    if (!match[x]) return augment(u, x), true;
                    Q.push(match[x]);
                    vis[match[x]] = 0;
                } else if (vis[x] == 0 && orig[v] != orig[x]) {
                    int a = lca(orig[v], orig[x]);
                    blossom(x, v, a);
                    blossom(v, x, a);
                }
            }
        }
        return false;
    }

    int maximum_matching() {
        int ans = 0;
        vector<int> p(n - 1);
        iota(p.begin(), p.end(), 1);
        shuffle(p.begin(), p.end(), rnd);
        for (int i = 1; i <= n; i++) shuffle(g[i].begin(), g[i].end(), rnd);
        for (auto u: p) {
            if (!match[u]) {
                for (auto v: g[u]) {
                    if (!match[v]) {
                        match[u] = v, match[v] = u;
                        ++ans;
                        break;
                    }
                }
            }
        }
        for (int i = 1; i <= n; ++i) if (!match[i] && bfs(i)) ++ans;
        return ans;
    }
} M;

int n, m;

void dowork() {
    cin >> n >> m;
    M = Blossom(n);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        u++, v++;
        M.add_edge(u, v);
    }

    cout << M.maximum_matching() << '\n';
    for (int i = 1; i <= n; ++i) {
        if (i < M.match[i]) cout << i - 1 << ' ' << M.match[i] - 1 << '\n';
    }
}
