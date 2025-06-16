struct SegmentTree {
private:
    vector<ll> seg;
    vector<ll> lazy; // update the ignore value
    int sz = 1;
    int mul(int a,int b){
        return (a*b)%mod;
    }

    int merge(int a, int b) {
        return (a+b)%mod;
    }
    void build(int n ,int x,int lx,int rx){
        if(lx==rx){
            if(rx<n){
                seg[x]=a[lx];
            }
            return;
        }
        int mid=(lx+rx)>>1;
        build(n,2*x+1,lx,mid);
        build(n,2*x+2,mid+1,rx);
        seg[x]= merge(seg[2*x+1],seg[2*x+2]);
    }

    void propagate(int x, int lx, int rx) {
        if (lazy[x]==1) { //
            return;
        }
        if(lx!=rx){
            lazy[2*x+1]= mul(lazy[2*x+1],lazy[x]);
            lazy[2*x+2]= mul(lazy[2*x+2],lazy[x]);
        }
        seg[x]= mul(seg[x],lazy[x]);
        lazy[x]=1;
    }

    void update(int l, int r, int v, int x, int lx, int rx) {
        propagate(x,lx,rx);
        if (l <= lx && rx <= r) {
            lazy[x]= mul(lazy[x],v);
            propagate(x,lx,rx);
            return;
        }
        if (r < lx || rx < l)return;
        int m = (rx + lx) >> 1;
        update(l, r, v, x * 2 + 1, lx, m);
        update(l, r, v, x * 2 + 2, m + 1, rx);
        seg[x]= merge(seg[2*x+1],seg[2*x+2]);
    }

    int query(int l, int r, int x, int lx, int rx) {
        propagate(x,lx,rx);
        if (lx > r or rx < l) {
            return 0;
        }
        if (lx >= l and rx <= r) {
            return seg[x];
        }
        int mid = (lx + rx) >> 1;
        return merge(query(l,r,2*x+1,lx,mid), query(l,r,2*x+2,mid+1,rx));
    }
 
public:
    SegmentTree(int n) {
        sz = 1;
        while (sz < n)sz <<= 1;
        seg = vector<ll>(sz << 1, 0);
        lazy = vector<ll>(sz << 1,1); // update the ignore value
        build(n,0,0,sz-1);
    }

    void update(int l, int r, int v) {
        update(l, r, v, 0, 0, sz - 1);
    }

    int query(int l, int r) {
        return query(l, r, 0, 0, sz - 1);
    }
};
