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


// to loop on the subsets of a mask 
for(int i = mask; i > 0; i = (i-1) & mask){
    	//gurantee that (mask|i==mask)
}

//if i'm looping on the masks and i need the answer of a previous mask
for(int mask = 0; mask < (1<<N); ++mask){
	dp[mask][-1] = A[mask];	//handle base case separately (leaf states)
	for(int i = 0;i < N; ++i){
		if(mask & (1<<i))
			dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
		else
			dp[mask][i] = dp[mask][i-1];
	}
	F[mask] = dp[mask][N-1];
}


