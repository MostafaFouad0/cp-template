dp[1][1] = 1;
    for (int i = 1; i < n; ++i) {
        for (int comp = 1; comp <= i; ++comp) {
            dp[i + 1][comp + 1] =
                    (dp[i + 1][comp + 1] + dp[i][comp] * (comp + 1)) % M; // add a new component with only number i

            dp[i + 1][comp] =
                    (dp[i + 1][comp] + dp[i][comp] * 2 * comp) % M; // insert number i at the end or begin of a component

            dp[i + 1][comp - 1] =
                    (dp[i + 1][comp - 1] + dp[i][comp] * (comp - 1)) % M; // merging two adjacent components and i between them
        }
    }
    cout << dp[n][1];
