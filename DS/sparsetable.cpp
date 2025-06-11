int st[N][25];
void build(int *a, int n) {
    for (int i = 0; i < n; ++i) {
        st[i][0] = a[i];
    }
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
            st[i][j] = (st[i][j - 1] & st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int pw = log2(r - l + 1); // could be better by precomputation
    return (st[l][pw] & st[r - (1 << (pw)) + 1][pw]);
}
