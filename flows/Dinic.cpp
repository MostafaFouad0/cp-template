//O(sqrt(n)*m))
int const N = 1e5 + 1, M = 2e5 + 1;
//Be carful : N-> nodes M-> is the number of edges*2
int head[N], work[N], to[M], nxt[M], cap[M], ne = 0, n, m, idx;

void init() {
    ne = 0;
    memset(head, -1, n * sizeof head[0]);
}

void addEdge(int f, int t, int c) {
    to[ne] = t;
    cap[ne] = c;
    nxt[ne] = head[f];
    head[f] = ne++;
}

void addAugEdge(int u, int v, int fc, int bc = 0) {
    addEdge(u, v, fc);
    addEdge(v, u, bc);
}

#define edges(u, v, e, c)  for(int e=head[u],c,v;~e && (c=cap[e],v=to[e],1);e=nxt[e])

int vis[N], vid;
int src, snk;

int dist[N];

bool bfs() {
    vis[src] = ++vid;
    dist[src] = 0;
    queue<int> q;
    q.push(src);
    while (q.size()) {
        int u = q.front();
        q.pop();
        edges(u, v, e, c)
            if (c && vis[v] != vid) {
                vis[v] = vid;
                dist[v] = dist[u] + 1;
                if (v == snk)
                    return 1;
                q.push(v);
            }
    }
    return 0;
}


int dfs(int u, int f = INT_MAX) {
    if (vis[u] == vid) return 0;
    if (u == snk or !f)
        return f;
    vis[u] = vid;
    for (int &e = work[u], c, v; ~e && (c = cap[e], v = to[e], 1); e = nxt[e]) {
        if (dist[u] + 1 != dist[v])continue;
        int df;
        if (df = dfs(v, min(f, c))) {
            cap[e] -= df;
            cap[e ^ 1] += df;
            return df;
        }
    }
    return 0;
}

int maxflow() {
    int flow = 0;
    while (bfs()) {
        memcpy(work, head, n * sizeof head[0]);
        for (int f; ++vid, f = dfs(src); flow += f);
    }
    return flow;
}

void dowork() {
    cin >> n >> m;
    init();
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        addAugEdge(a, b, c, c);
    }

    src = 0, snk = n - 1;
    cout << maxflow();
}
