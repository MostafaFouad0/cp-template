struct disjoint_sparse_table {
    int n;
    vector<int> a;
    vector<vector<int>> table;

    disjoint_sparse_table(vector<int> in) {
        a = in;
        n = a.size();
    }

    void build() {
        int lg{};
        while ((1 << lg) < n) lg++;
        table = vector<vector<int>>(lg, vector<int>(n));
        for (int i = 0; i < lg; ++i) {
            int len = 1 << (i + 1);
            int mid_offset = 1 << i;
            for (int start = 0; start < n; start += len) {
                int mid = start + mid_offset;
                if (mid >= n) break;
                int cur = a[mid - 1] % p;
                table[i][mid - 1] = cur;
                for (int j = mid - 2; j >= start; --j) {
                    cur = (a[j] * cur) % p;
                    table[i][j] = cur;
                }
                cur = a[mid] % p;
                table[i][mid] = cur;
                int end = min(start + len, n);
                for (int j = mid + 1; j < end; ++j) {
                    cur = (cur * a[j]) % p;
                    table[i][j] = cur;
                }
            }
        }
    }

    int qry(int l, int r) {
        if (l == r) return a[l] % p;
        int k = 31 - __builtin_clz(l ^ r);
        return (table[k][l] * table[k][r]) % p;
    }
};
