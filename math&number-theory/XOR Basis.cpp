const int B = 63;
struct Basis {
    int sz = 0;
    vector<int> b;

    Basis(): b(vector<int>(B)) {}

    void insert(int x) {
        for(int i = B - 1; ~i; --i) {
            if(!(x >> i & 1)) continue;
            if(!b[i]) {
                b[i] = x, ++sz;
                return;
            }
            x ^= b[i];
        }
    }

    bool can(int x) {
        for(int i = B - 1; ~i; --i) {
            if(!(x >> i & 1)) continue;
            if(!b[i]) return 0;
            x ^= b[i];
        }
        return !x;
    }

   int max_xor(int ans = 0) {
        for(int i = B - 1; i >= 0; i--) {
            ans = max(ans, ans ^ b[i]);
        }
        return ans;
    }
};
