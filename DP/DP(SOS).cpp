//number of elements that x&y == x  (1)
for (int i = 0; i < 20; ++i) {
        for (int msk = N - 1; msk >= 0; --msk) {
            if (!(msk & (1 << i))) dp2[msk] += dp2[msk ^ (1 << i)];
        }
    }

//number of elements that x|y == x  (2)
for (int i = 0; i < 20; ++i) {
        for (int msk = 0; msk < N; ++msk) {
            if (msk & (1 << i)) dp1[msk] += dp1[msk ^ (1 << i)];
        }
    }

//subsequence there OR exactly == x  (3)
for (int i = 0; i < n; ++i) {
        for (int msk = 0; msk < (1 << n); ++msk) {
            if (msk & (1 << i)) dp[msk] = (dp[msk] + M - dp[msk ^ (1 << i)]) % M;
        }
    }

//number of elements that x&y != 0 
//use method 2 and answer is -> (total - dp[msk^((1<<n)-1)])

