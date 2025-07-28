struct Tree {
private:
    vector<vector<int>> seg;
    Tree(int size) {
        sz = 1;
        while (sz < size) sz <<= 1;
        seg = vector<vector<int>>(sz << 1);
    }

    void merge(vector<int> &v, vector<int> &l, vector<int> &r) {
        int i = 0, j = 0, vv = 0;
        while (i < l.size() && j < r.size()) {
            if (l[i] <= r[j]) v[vv++] = l[i++];
            else v[vv++] = r[j++];
        }

        for (int k = i; k < l.size(); k++) v[vv++] = l[k];
        for (int k = j; k < r.size(); k++) v[vv++] = r[k];
    }

    void update(int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < n)
                seg[x].emplace_back(interval[lx].second);
            return;
        }
        int md = (lx + rx) >> 1;
        update(2 * x + 1, lx, md);
        update(2 * x + 2, md + 1, rx);
        seg[x].resize(seg[2 * x + 1].size() + seg[2 * x + 2].size());
        merge(seg[x], seg[2 * x + 1], seg[2 * x + 2]);
    }

    int query(int l, int r, int v, int x, int lx, int rx) {
        if (r < lx || rx < l) return 0;
        if (l <= lx && rx <= r) return lower_bound(seg[x].begin(), seg[x].end(), v) - seg[x].begin();
        int md = (lx + rx) >> 1;
        return query(l, r, v, 2 * x + 1, lx, md) + query(l, r, v, 2 * x + 2, md + 1, rx);
    }

};
