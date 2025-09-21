//O(N * M^2)
int const N = 1e5 + 1, M = 2e5 + 1;
//Be carful : N-> nodes M-> is the number of edges*2

int head[N], to[M], nxt[M], cap[M], ne;
int n, m, idx;

void init() {
    ne = 0;
    memset(head, -1, n * sizeof head[0]);
}

void addEdge(int f, int t, int c) {//f-> from t-> to c-> cap
    to[ne] = t;
    cap[ne] = c;
    nxt[ne] = head[f];
    head[f] = ne++;
}

void addAugEdge(int u, int v, int fc, int bc = 0) {//f-> from t-> to c-> cap
    addEdge(u, v, fc);
    addEdge(v, u, bc);
}

#define edges(u, v, e, c) for(int e=head[u],c,v;~e && (c=cap[e],v=to[e],1);e=nxt[e])

int vis[N], vid;
int src, snk;

int par[N], flow[N];

int bfs() {
    vis[src] = ++vid;
    par[src] = -1;
    flow[src] = INT_MAX;
    queue<int> q;
    q.push(src);
    while (q.size()) {
        int u = q.front();
        q.pop();
        edges(u, v, e, c)if (c and vis[v] != vid) {
                vis[v] = vid;
                par[v] = e;
                flow[v] = min(flow[u], c);
                if (v == snk) return flow[snk];
                q.push(v);
            }
    }
    return 0;
}

int maxflow() {
    int flow{};
    for (int f; f = bfs(); flow += f)
        for (int e = par[snk]; ~e; e = par[to[e ^ 1]]) {
            cap[e] -= f;
            cap[e ^ 1] += f;
        }
    return flow;
}

signed main() {
    cin>>n>>m; //n edges - m nodes
    init();
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        addAugEdge(a, b, c);
    }

    src = 1, snk = m;
    cout << maxflow();
}
