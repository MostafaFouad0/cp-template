void pre() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = i * fact[i - 1] % mod;
        inv[i] = modpow(fact[i], mod - 2);
    }
}

int nCr(int i,int j) {
    return fact[i] * inv[j] % mod * inv[i - j] % mod;
}

int nPr(int i,int j) {
    return fact[i] * inv[j] % mod ;
}

int starsAndBars(int n,int k) {
    return nCr(n + k - 1, k);
}

int lucas(int n, int r) {
    if (r > n || n < mod) return nCr(n, r);
    return 1LL * lucas(n / mod, r / mod) * lucas(n % mod, r % mod) % mod;
}

void pascalTriangle(){
    comb[0][0] = 1;
    for (int i = 1; i <= MAX; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++)
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
    }
}
