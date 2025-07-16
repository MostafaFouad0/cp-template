void Task() {
    string s;
    int q;
    cin >> s >> q;
    const auto p = build(s);
    int n = p.size();
    /* for (int i = 0; i < p.size(); ++i) {
         cout << p[i] << ' ';
     }
     cout << '\n';*/
    vector<int> res(q, -1);
    vector<array<int, 4>> qu[n];
    for (int i = 0; i < q; ++i) {
        int k;
        string m;
        cin >> k >> m;
        int l = 1, r = p.size() - 1, md, lo = 0, hi = -1;
        while (l <= r) {
            md = l + r >> 1;
            string cur = s.substr(p[md], min((int) m.size(), (int) (s.size() - p[md])));
            if (cur == m) {
                lo = md;
                r = md - 1;
            } else if (cur > m) {
                r = md - 1;
            } else {
                l = md + 1;
            }
        }
 
        l = 1, r = p.size() - 1;
        while (l <= r) {
            md = l + r >> 1;
            string cur = s.substr(p[md], min((int) m.size(), (int) (s.size() - p[md])));
            if (cur == m) {
                hi = md;
                l = md + 1;
            } else if (cur < m) {
                l = md + 1;
            } else {
                r = md - 1;
            }
        }
 
        if (lo <= hi) qu[hi].push_back({lo, k, (int) m.size(), i});
        //cout << lo << ' ' << hi << '\n';
    }
 
    for (int i = 1; i < n; ++i) {
        set<int> st;
        sort(qu[i].rbegin(), qu[i].rend());
        int r = i;
        for (auto [l, k, m, id]: qu[i]) {
            while (r >= l) st.insert(p[r]), r--;
 
            auto it1 = st.begin(), it2 = st.begin();
            int rem = k - 1;
            while (rem) {
                if (it2 != st.end()) it2++, rem--;
                else break;
            }
 
            if (it2 == st.end() or rem) continue;
 
            res[id] = n + 1;
            while (it2 != st.end()) {
                res[id] = min(res[id], *it2 - *it1 + m);
                it2++;
                it1++;
            }
        }
    }
 
    for (int i = 0; i < q; ++i) {
        cout << res[i] << '\n';
    }
}
