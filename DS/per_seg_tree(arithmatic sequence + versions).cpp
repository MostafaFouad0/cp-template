//not using pointers so mansour won't be mad
//Peristent segment tree with versions (arithematic sequence : a, a+b, a+2*b, ...)
int L[100 * N], R[100 * N], Sum[100 * N];//100 is logn for newparent + logn*2*2 for propagation
pair<int, int> Lazy[100 * N];

struct persg {
    int ptr;

    persg() {
        ptr = 0;
    }

    int newParent(int l, int r) {
        ptr++;
        L[ptr] = l, R[ptr] = r;
        Sum[ptr] = Sum[l] + Sum[r];
        return ptr;
    }

    int newLazy(int lx, int rx, int node, int a, int b) {
        ptr++;
        L[ptr] = L[node], R[ptr] = R[node];
        Lazy[ptr].first = Lazy[node].first + a;
        Lazy[ptr].second = Lazy[node].second + b;
        int rng = rx - lx + 1;
        Sum[ptr] = Sum[node] + a * rng + b * ((rng * (rng - 1)) / 2);
        return ptr;
    }

    void propagate(int lx, int rx, int node) {
        if (lx == rx) return;
        if (Lazy[node].first or Lazy[node].second) {
            int md = lx + rx >> 1;
            L[node] = newLazy(lx, md, L[node], Lazy[node].first, Lazy[node].second);
            R[node] = newLazy(md + 1, rx, R[node], Lazy[node].first + (md - lx + 1) * Lazy[node].second,
                              Lazy[node].second);
        }
        Lazy[node].first = Lazy[node].second = 0;
    }

    int update(int l, int r, int node, int a, int b, int lx = 0, int rx = n - 1) {
        if (r < lx or rx < l) return node;
        if (l <= lx and rx <= r) return newLazy(lx, rx, node, a + (lx - l) * b, b);
        propagate(lx, rx, node);
        int md = lx + rx >> 1;
        return newParent(update(l, r, L[node], a, b, lx, md), update(l, r, R[node], a, b, md + 1, rx));
    }

    int query(int l, int r, int node, int lx = 0, int rx = n - 1) {
        if (r < lx or rx < l or !node) return 0;
        if (l <= lx and rx <= r) return Sum[node];
        propagate(lx, rx, node);
        int md = lx + rx >> 1;
        return query(l, r, L[node], lx, md) + query(l, r, R[node], md + 1, rx);
    }

};
