struct BIT {
    vector<int> bit;
    int size;

    BIT(int n) : size(n + 1) {
        bit = vector<int>(size);
    }

    void add(int idx, int v) {
        for (++idx; idx < size; idx += idx & -idx)
            bit[idx] += v;
    }

    int sum(int idx) {
        int res{};
        for (++idx; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
