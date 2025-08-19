//number of elements that x&y == x
for (int i = 0; i < 20; ++i) {
        for (int msk = N - 1; msk >= 0; --msk) {
            if (!(msk & (1 << i))) dp2[msk] += dp2[msk ^ (1 << i)];
        }
    }

//number of elements that x|y == x
for (int i = 0; i < 20; ++i) {
        for (int msk = 0; msk < N; ++msk) {
            if (msk & (1 << i)) dp1[msk] += dp1[msk ^ (1 << i)];
        }
    }

