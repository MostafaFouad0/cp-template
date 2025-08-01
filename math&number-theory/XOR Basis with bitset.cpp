const int B = 251;
struct Basis {
    int sz = 0;
    vector<bitset<B>> b;

    Basis() : b(vector<bitset<B>>(B)) {}

      bool all_zeros(bitset<B> &x) {
        return x.none();
    }

    void insert(bitset<B> x) {
        for (int i = B - 1; ~i; --i) {
            if (!x[i]) continue;
            if (all_zeros(b[i])) {
                b[i] = x, ++sz;
                return;
            }
            x ^= b[i];
        }
    }

    bool can(bitset<B> x) {
        for (int i = B - 1; ~i; --i) {
            if (!x[i]) continue;
            if (all_zeros(b[i])) return 0;
            x ^= b[i];
        }
        return all_zeros(x);
    }
};
