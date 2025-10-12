struct BIT {
    vector<int> bit;
    int size;

    BIT(int n) : size(n), bit(n + 1) {}

    void add(int i, int x) {
        for (int j = i; j < size; j += j & -j) bit[j] += x;
    }

    int sum(int idx) {
        int res{};
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    //get the first prefix that >= v
    int lowerBound(int v) {
        int pos = 0;
        for (int i = __lg(size); ~i; --i)
            if (pos + (1 << i) < size && bit[pos + (1 << i)] < v) {
                v -= bit[pos + (1 << i)];
                pos += 1 << i;
            }
        return pos + 1;
    }

    //for the update range : (need two bit) 
     void add(int l, int r, int x) {
        add(bit, l, x);
        add(bit, r, -x);
        add(bit2, l, x * (l - 1));
        add(bit2, r, -x * r);
    }

    int sum(int l, int r) {
        return (sum(bit, r) * r - sum(bit2, r)) - (sum(bit, l - 1) * (l - 1) - sum(bit2, l - 1));
    }
};
