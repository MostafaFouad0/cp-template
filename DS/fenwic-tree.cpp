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
};
