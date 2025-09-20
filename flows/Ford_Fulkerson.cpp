//O(maxflow*edges)

int const N = 1e5 + 1, M = 2e5 + 1;
//Be carful : N-> nodes M-> is the number of edges*2

int head[N], to[M], nxt[M], cap[M], ne;
int n, q, idx;

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

int dfs(int u, int f = INT_MAX) {
    if (u == snk or !f or vis[u] == vid) return f;
    vis[u] = vid;
    edges(u, v, e, c) {
        int df = dfs(v, min(f, c));
        if (df > 0) {
            cap[e] -= df;
            cap[e ^ 1] += df;
            return df;
        }
    }
    return 0;
}

int maxflow() {
    int flow{};
    for (int f; ++vid, f = dfs(src); flow += f);
    return flow;
}
