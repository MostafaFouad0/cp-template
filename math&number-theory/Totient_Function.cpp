void totient() {
    for (int i = 1; i < N2; ++i) {
        phi[i] = i;
    }
    for (int i = 2; i < N2; ++i) {
        if (phi[i] == i) {
            for (int j = i; j < N2; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
};

// phi(N!) = (N is prime ? N-1 : N ) * phi( (N-1)!)
ll phi_factn(int n) {

    ll ret = 1;
    for (int i = 2; i <= n; ++i)
        ret = ret * (isprime(i) ? i - 1 : i);
    return ret;
}
