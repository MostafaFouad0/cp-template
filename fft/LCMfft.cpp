//Be carfeful ! : O(nloglogn)
vector<int> PrimeEnumerate(int n) {
    vector<int> P;
    vector<bool> B(n + 1, 1);
    for (int i = 2; i <= n; i++) {
        if (B[i]) P.push_back(i);
        for (int j: P) {
            if (i * j > n) break;
            B[i * j] = 0;
            if (i % j == 0) break;
        }
    }
    return P;
}

void DivisorZetaTransform(vector<int> &v) {
    const int n = (int) v.size() - 1;
    for (int p: PrimeEnumerate(n)) {
        for (int i = 1; i * p <= n; i++)
            v[i * p] += v[i], v[i * p] %= M;
    }
}

void DivisorMobiusTransform(vector<int> &v) {
    const int n = (int) v.size() - 1;
    for (int p: PrimeEnumerate(n)) {
        for (int i = n / p; i; i--)
            v[i * p] = (v[i * p] - v[i] + M) % M;
    }
}

vector<int> LCMConvolution(vector<int> A, vector<int> B) {
    DivisorZetaTransform(A);
    DivisorZetaTransform(B);
    for (int i = 0; i < A.size(); i++) A[i] = (A[i] * B[i]) % M;
    DivisorMobiusTransform(A);
    return A;
}
