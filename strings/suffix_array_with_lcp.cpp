void radix_sort(vector<pair<pair<int, int>, int>>& a)
{
    int n = a.size();
    {
        vector<int> cnt(n);
        for (const auto it : a)
        {
            cnt[it.F.S]++;
        }
        vector<pair<pair<int, int>, int>> a_new(n);
        vector<int> pos(n);
        for (int i = 1; i < n; i++)
        {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for (auto it : a)
        {
            int i = it.F.S;
            a_new[pos[i]] = it;
            pos[i]++;
        }
        a.swap(a_new);
    }

    {
        vector<int> cnt(n);
        for (const auto it : a)
        {
            cnt[it.F.F]++;
        }
        vector<pair<pair<int, int>, int>> a_new(n);
        vector<int> pos(n);
        for (int i = 1; i < n; i++)
        {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for (auto it : a)
        {
            int i = it.F.F;
            a_new[pos[i]] = it;
            pos[i]++;
        }
        a.swap(a_new);
    }
}


pair<vector<int>, vector<int>> build(string& s)
{
    /// return {suffixArray, LCP}
    s += '$';
    int n = s.size();
    vector<int> p(n), c(n), lcp(n);
    {
        /// k=0
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++)a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++)p[i] = a[i].S;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i].F == a[i - 1].F)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
    }
    int k = 0;
    while ((1 << k) < n)
    {
        /// calculate k+1
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        radix_sort(a);
        for (int i = 0; i < n; i++)p[i] = a[i].S;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i].F == a[i - 1].F)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
        k++;
    }
    k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int pi = c[i];
        int j = p[pi - 1];
        while (s[i + k] == s[j + k])k++;
        lcp[pi] = k;
        k = max(k - 1, 0ll);
    }
    return {p, lcp};
}
