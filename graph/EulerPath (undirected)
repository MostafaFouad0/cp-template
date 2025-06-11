//to check if there is a path such that each edge visited exactly once 

int const N = 4e5 + 1, M = 4e5 + 1;//N-> nodes , M-> edges
//basically for each edge i want two things:
//this edge goes to what node (call it array to)
//the next edge after it (call it array nxt)
//we will need array head to help us get the next edge
int head[N], nxt[M], to[M], ne, n, sz;

//make a define loop to loop on the edges
#define edge(u, v, e) for(int v, e=head[u];~e&&(v=to[e],1);e=nxt[e])

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
