struct matrix {
    int a[2][2];

    matrix() { memset(a, 0, sizeof a); }

    matrix operator*(const matrix &b) {
        matrix res;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % M;
        return res;
    }
};

void mat_pow(matrix &a, matrix base, int power) {
    while (power) {
        if (power & 1) a = (a * base);
        base = (base * base);
        power /= 2;
    }
}
