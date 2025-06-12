//to check if there is a path that each edges visited exactly once (for a connected component)
//if the degrees of all nodes are even : any start will be a solution
//if the degrees of all nodes are even but exactly two odd : one of the two odds will be the start (it is impossible to have one odd degree)

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

bool geteuler() {
    int cnt = count(evenDeg, evenDeg + n, 1);
    if (cnt > 2) return false;
    int s = cnt ? find(evenDeg, evenDeg + n, 1) - evenDeg : 0;
    euler(s);
    return 1;
}

signed main(){
    init();
    vid++;
    for (int i = 0; i < n; ++i) {
        int U, V;
        addedge(U, V);
        addedge(V, U);
        evenDeg[U] ^= 1;
        evenDeg[V] ^= 1;
    }

    if(geteuler() and sz==m){ //m->number of edges
        for (int i = sz - 1; ~i; --i) cout << ans[i] / 2 + 1 << ' ';
    } else {
        cout<<-1;
    }
}
