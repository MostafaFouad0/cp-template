#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
using namespace std;

#define ll long long
//#define int long long

int const N = 2e5 + 5, LOG = 17, N2 = 1e5 + 5, M = 1e9 + 7;
int n, idx, SQ, q;

struct Query {
    int l, r, timer, id;

    Query() {}

    Query(int l, int r, int timer, int id) : l(l), r(r), timer(timer), id(id) {}

    bool operator<(Query &other) const {
        if (l / SQ == other.l / SQ) {
            if (r / SQ == other.r / SQ) {
                return timer < other.timer;
            }
            return r / SQ < other.r / SQ;
        }
        return l / SQ < other.l / SQ;
    }
};

vector<int> cmp;

void comp(vector<int> &a, vector<char> ty, vector<int> &y) {
    for (int i = 0; i < a.size(); ++i) {
        cmp.emplace_back(a[i]);
    }
    for (int i = 0; i < q; ++i) {
        if (ty[i] == 'U') {
            cmp.emplace_back(y[i]);
        }
    }
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    for (int i = 0; i < a.size(); ++i) {
        a[i] = lower_bound(cmp.begin(), cmp.end(), a[i]) - cmp.begin();
    }
    for (int i = 0; i < q; ++i) {
        if (ty[i] == 'U') {
            y[i] = lower_bound(cmp.begin(), cmp.end(), y[i]) - cmp.begin();
        }
    }
}

vector<int> a, frq;

void add(int i, ll &cur) {
    i = a[i];
    if (!frq[i]) cur += cmp[i];
    frq[i]++;
}

void erase(int i, ll &cur) {
    i = a[i];
    if (frq[i] == 1) cur -= cmp[i];
    frq[i]--;
}

void update(int i, int x, int l, int r, ll &cur) {
    if (l <= i and i <= r) {
        frq[a[i]]--;
        if (frq[a[i]] == 0) cur -= cmp[a[i]];
        a[i] = x;
        frq[a[i]]++;
        if (frq[a[i]] == 1) cur += cmp[a[i]];
    } else {
        a[i] = x;
    }
}

void dowork() {
    cin >> n;
    a = vector<int>(n);
    for (auto &i: a) cin >> i;
    cin >> q;
    vector<char> ty(q);
    vector<int> x(q), y(q);
    for (int i = 0; i < q; ++i) {
        cin >> ty[i] >> x[i] >> y[i];
    }
    comp(a, ty, y);
    vector<vector<int>> st(n);
    for (int i = 0; i < n; ++i) {
        st[i].emplace_back(a[i]);
    }
    SQ = 1;
    while (SQ * SQ * SQ <= 2 * n * n) SQ++;

    vector<Query> qu;
    vector<pair<int, int>> up;
    for (int i = 0; i < q; ++i) {
        if (ty[i] == 'U') {
            up.emplace_back(--x[i], y[i]);
        } else {
            qu.emplace_back(--x[i], --y[i], up.size(), qu.size());
        }
    }

    if (qu.empty()) return;
    sort(qu.begin(), qu.end());
    int l = qu[0].l, r = l - 1;
    vector<ll> res(qu.size());
    frq = vector<int>(cmp.size() + 1);
    ll cur{}, timer{};
    auto update = [&](int i, int x, int l, int r) {
        if (l <= i and i <= r) {
            frq[a[i]]--;
            if (frq[a[i]] == 0) cur -= cmp[a[i]];
            a[i] = x;
            frq[a[i]]++;
            if (frq[a[i]] == 1) cur += cmp[a[i]];
        } else {
            a[i] = x;
        }
    };

    for (auto const &[lq, rq, timerq, id]: qu) {
        while (timer < timerq) {
            st[up[timer].first].emplace_back(up[timer].second);
            update(up[timer].first, st[up[timer].first].back(), l, r);
            timer++;
        }

        while (timer > timerq) {
            timer--;
            st[up[timer].first].pop_back();
            update(up[timer].first, st[up[timer].first].back(), l, r);
        }

        while (r < rq) add(++r, cur);
        while (lq < l) add(--l, cur);

        while (rq < r) erase(r--, cur);
        while (l < lq) erase(l++, cur);
        res[id] = cur;
    }

    for (auto i: res) cout << i << '\n';
}


signed main() {
    Pc_champs
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        idx++;
        dowork();
        cout << "\n";
    }
}
