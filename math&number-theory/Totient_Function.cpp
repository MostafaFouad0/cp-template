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
