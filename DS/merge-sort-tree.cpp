vector<vector<int>> tree(4 * N);

void build(int x,int lx,int rx)
{
    if (lx == rx)
    {
        tree[x].push_back(a[lx]);
        return;
    }
    int mid = (lx + rx) / 2;
    build(x * 2 + 1, lx, mid);
    build(x * 2 + 2, mid + 1, rx);
    merge(tree[2 * x + 1].begin(), tree[2 * x + 1].end(),
          tree[2 * x + 2].begin(), tree[2 * x + 2].end(),
          back_inserter(tree[x]));
}

int query(int x,int lx,int rx,int l,int r,int val)
{
    if (lx > r or rx < l)return 0;
    if (lx >= l and rx <= r)
    {
        return upper_bound(tree[x].begin(), tree[x].end(), val) - tree[x].begin(); /// update this if needed
    }
    int mid = (lx + rx) / 2;
    return query(2 * x + 1, lx, mid, l, r, val)
        + query(2 * x + 2, mid + 1, rx, l, r, val);
}
