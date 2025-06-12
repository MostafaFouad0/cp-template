//to check if there is a path that each edges visited exactly once (for a connected component)

int const N = 4e5 + 1, M = 4e5 + 1; //N->nodes , M->edges
int head[N], nxt[M], to[M], ne, n, sz;

bool evenDeg[N];

void init() {
    memset(head, -1, n * sizeof head[0]);
    memset(evenDeg, 0, n * sizeof evenDeg[0]);
    ne = sz = 0;
}

void addedge(int u, int v) {
    nxt[ne] = head[u];
    head[u] = ne;
    to[ne++] = v;
}

int ans[M];
int vis[M], vid;

void euler(int u) {
    for (int v, &e = head[u]; ~e && (v = to[e], 1);) {
        int ee = e;
        e = nxt[e];
        if (vis[ee] == vid) continue;
        vis[ee ^ 1] = vid;
        euler(v);
        ans[sz++] = ee;
    }
}

bool iseuler() {
    int cnt = count(evenDeg, evenDeg + n, 1);
    return cnt <= 2;
}
