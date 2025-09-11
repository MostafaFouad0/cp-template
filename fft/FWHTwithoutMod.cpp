//OR
void fwht_or(vector<int> &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; ++i) {
                a[l + h + i] += a[l + i];
            }
        }
    }
}

void ifwht_or(vector<int> &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; ++i) {
                a[l + h + i] -= a[l + i];
            }
        }
    }
}

//AND
void fwht_and(vector<int> &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; ++i) {
                a[l + i] += a[l + i + h];
            }
        }
    }
}

void ifwht_and(vector<int> &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; ++i) {
                a[l + i] -= a[l + i + h];
            }
        }
    }
}

//XOR
void fwht_xor(vector<int> &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; ++i) {
                int tmp = a[l + h + i];
                a[l + h + i] = a[l + i] - tmp;
                a[l + i] += tmp;
            }
        }
    }
}

void ifwht_xor(vector<int> &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; ++i) {
                int tmp = a[l + h + i];
                a[l + h + i] = (a[l + i] - tmp) / 2;
                a[l + i] = (a[l + i] + tmp) / 2;
            }
        }
    }
}

vector<int> conv_xor(vector<int> &a, vector<int> &b) {
    int n = max(a.size(), b.size());
    int sz = 1;
    while (sz < n) sz <<= 1;

    vector<int> A = a, B = b;
    A.resize(sz);
    B.resize(sz);

    fwht_xor(A);//or fwht_or or fwht_and
    fwht_xor(B);//or fwht_or or fwht_and

    for (int i = 0; i < sz; ++i) A[i] *= B[i];

    ifwht_xor(A);//or ifwht_or or ifwht_and
    return A;
}

vector<int> poly_pow(vector<int> &a, int p) {
    vector<int> res;
    while (p) {
        if (p & 1) {
            if (res.size()) res = conv_and(res, a);
            else res = a;
        }
        a = conv_and(a, a);
        p >>= 1;
    }
    return res;
}
