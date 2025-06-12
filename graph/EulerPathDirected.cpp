//if degdiff: in - out : equal 0 for each node -> any start is valid
//if degdiff equal 0 for each node except two and one of them have defdiff=1 -> that will be the start                    : 
int const N = 4e5 + 1, M = 4e5 + 1;
int head[N], nxt[M], to[M], ne, n, sz;

int degDiff[N];

void init() {
    memset(head, -1, n * sizeof head[0]);
    memset(degDiff, 0, n * sizeof degDiff[0]);
    ne = sz = 0;
}

void addedge(int u, int v) {
    nxt[ne] = head[u];
    head[u] = ne;
    to[ne++] = v;
}

int ans[M];

void euler(int u) {
    for (int v, &e = head[u]; ~e && (v = to[e], 1);) {
        int ee = e;
        e = nxt[e];
        euler(v);
        ans[sz++] = ee;
    }
}

bool geteuler() {
    int cnt = count(degDiff, degDiff + n, 0);
    if (cnt < n - 2) return false;
    int s = 0;//zero means node 0
    if (cnt == n - 2) {
        s = find(degDiff, degDiff + n, 1) - degDiff;
        if (s == n) return false;
        euler(s);
    }
    return 1;
}

signed main() {
    init();
    for (int i = 0; i < n; ++i) {
        int U, V;
        addedge(U, V);
        degDiff[U]++;
        degDiff[V]--;
    }

    if (geteuler() and sz == m) {
        for (int i = sz - 1; ~i; --i) cout << ans[i] / 2 + 1 << ' ';
    } else {
        cout << -1;
    }
}
