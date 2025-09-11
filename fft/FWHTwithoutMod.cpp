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

vector<int> conv_or(vector<int> &a, vector<int> &b) {
    int n = max(a.size(), b.size());
    int sz = 1;
    while (sz < n) sz <<= 1;

    vector<int> A = a, B = b;
    A.resize(sz);
    B.resize(sz);

    fwht_or(A);
    fwht_or(B);

    for (int i = 0; i < sz; ++i) A[i] *= B[i];

    ifwht_or(A);
    return A;
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

vector<int> conv_and(vector<int> &a, vector<int> &b) {
    int n = max(a.size(), b.size());
    int sz = 1;
    while (sz < n) sz <<= 1;

    vector<int> A = a, B = b;
    A.resize(sz);
    B.resize(sz);

    fwht_and(A);
    fwht_and(B);

    for (int i = 0; i < sz; ++i) A[i] *= B[i];

    ifwht_and(A);
    return A;
}

//XOR

