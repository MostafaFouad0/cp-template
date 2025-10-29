struct Hash {
    vector<int> B = {29, 31}, M = {(int) 1e9 + 7, (int) 1e9 + 9};

    vector<vector<int>> pw, inv;

    Hash() {}

    Hash(int n) {
        pw = inv = vector<vector<int>>(2, vector<int>(n + 1));
        for (int i = 0; i < 2; ++i) {
            pw[i][0] = 1;
            inv[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 2; ++j) {
                pw[j][i] = (pw[j][i - 1] * B[j]) % M[j];
                inv[j][i] = fast_power(pw[j][i], M[j] - 2, M[j]);
            }
        }
    }

    array<int, 2> pushback(array<int, 2> h, int ch) {
        for (int i = 0; i < 2; ++i) {
            h[i] = (h[i] * B[i]) % M[i];
            h[i] = (h[i] + ch) % M[i];
        }
        return h;
    }

    array<int, 2> pushfront(array<int, 2> h, int ch, int sz) {// sz -> position of character (0 based)
        for (int i = 0; i < 2; ++i) {
            h[i] = (h[i] + (pw[i][sz] * ch)) % M[i];
        }
        return h;
    }

    array<int, 2> popback(array<int, 2> h, int ch) {
        for (int i = 0; i < 2; ++i) {
            h[i] = (h[i] - ch + M[i]) % M[i];
            h[i] = (h[i] * inv[i][1]) % M[i];
        }
        return h;
    }

    array<int, 2> popfront(array<int, 2> h, int ch, int sz) {// sz -> position of character (0 based)
        for (int i = 0; i < 2; ++i) {
            h[i] = (h[i] - (pw[i][sz] * ch) % M[i] + M[i]) % M[i];
        }
        return h;
    }

    array<int, 2> subsuf(array<int, 2> r, array<int, 2> l, int sz) {// if you have a suffix and getting a range
        for (int i = 0; i < 2; ++i) {
            r[i] = (r[i] - l[i] + M[i]) % M[i];
            r[i] = (r[i] * inv[i][sz]) % M[i];
        }
        return r;
    }

    array<int, 2> subpre(array<int, 2> r, array<int, 2> l, int sz) {// if you have a prefix and getting a range
        for (int i = 0; i < 2; ++i) {
            l[i] = (l[i] * pw[i][sz]) % M[i];
            r[i] = (r[i] - l[i] + M[i]) % M[i];
        }
        return r;
    }
} H;
