/// O(n log^2(n))
vector<int> build(string s)
{
    s += '$';
    int n = s.size();
    vector<int> p(n), c(n);
    {
        /// k=0
        vector<pair<int,int>> a(n);
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
        vector<pair<pair<int,int>,int>> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
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
        k++;
    }
    return p;
}
