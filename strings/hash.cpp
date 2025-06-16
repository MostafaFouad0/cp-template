vector<int> calc(string& s)
{
    int p = 31;
    int pow = 31;
    vector<int> pre_hash(s.size());
    pre_hash[0] = s[0] - 'a' + 1;
    inv[0] = 1;
    for (int i = 1; i < s.size(); ++i)
    {
        pre_hash[i] = (pre_hash[i - 1] + ((s[i] - 'a' + 1) * pow)) % MOD;
        inv[i] = power(pow, MOD - 2, MOD);
        pow = (pow * p) % MOD;
    }
    return pre_hash;
}

int get_hash(int l, int r, const vector<int>& pre_hash)
{
    int ret = ((pre_hash[r] - (l ? pre_hash[l - 1] : 0) + MOD) * inv[l]) % MOD;
    return ret;
}
