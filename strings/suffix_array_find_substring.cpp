// get the suffix array and binary search for the first string that has the query string as a prefix
void solve()
{
    string s;
    cin >> s;
    const auto p = build(s);
    int q;
    cin >> q;
    while (q--)
    {
        string x;
        cin >> x;
        int l{}, r = p.size()-1, mid, ans = -1;
        while (l <= r)
        {
            mid = (l + r) >> 1;
            string now = s.substr(p[mid], min((int)x.size(), (int)s.size() - p[mid] - 1));
            if (now == x)
            {
                ans = mid;
                r = mid - 1;
            }
            else if (now > x)r = mid - 1;
            else l = mid + 1;
        }
        if (ans != -1)
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
}
 
