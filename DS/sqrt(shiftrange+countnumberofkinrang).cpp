#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
using namespace std;

#define ll long long
#define int long long

int const N = 1e5 + 5, LOG = 17, N2 = 1e5 + 5, M = 1e9 + 7;
int n, q, idx, SQ;
vector<int> a, sz;
vector<vector<int>> blck, ele;

void build() {
    int prv{};
    for (int i = 0; i < SQ; ++i) {
        for (int j = 0; j < sz[i]; ++j) {
            int ind = prv + j;
            a[ind] = blck[i][j];
            ele[i][a[ind]] = 0;
            blck[i][j] = 0;
        }
        prv += sz[i];
        sz[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        sz[i / SQ]++;
        blck[i / SQ][i % SQ] = a[i];
        ele[i / SQ][a[i]]++;
    }
}

void shift(int l, int r) {
    if (l == r) return;
    int prv{};
    int rele;
    for (int i = 0; i < SQ; ++i) {
        prv += sz[i];
        if (prv >= r + 1) {
            prv -= sz[i];
            int ind = r - prv;
            rele = blck[i][ind];
            ele[i][rele]--;
            for (int j = ind + 1; j < sz[i]; ++j) {
                blck[i][j - 1] = blck[i][j];
            }
            sz[i]--;
            break;
        }
    }

    prv = 0;
    for (int i = 0; i < SQ; ++i) {
        prv += sz[i];
        if (prv >= l + 1) {
            prv -= sz[i];
            int ind = l - prv;
            sz[i]++;
            for (int j = sz[i] - 1; j > ind; --j) {
                blck[i][j] = blck[i][j - 1];
            }
            blck[i][ind] = rele;
            ele[i][rele]++;
            break;
        }
    }
}

int Query(int l, int r, int k) {
    int prv{};
    int tot{};
    for (int i = 0; i < SQ; ++i) {
        prv += sz[i];
        if (prv >= l + 1) {
            prv -= sz[i];
            int ind = l - prv;
            for (int j = 0; j <= ind; ++j) {
                tot -= (blck[i][j] == k);
            }
            break;
        }
        tot -= ele[i][k];
    }

    prv = 0;
    for (int i = 0; i < SQ; ++i) {
        prv += sz[i];
        if (prv >= r + 1) {
            prv -= sz[i];
            int ind = r - prv;
            for (int j = 0; j <= ind; ++j) {
                tot += (blck[i][j] == k);
            }
            break;
        }
        tot += ele[i][k];
    }
    return tot;
}

void dowork() {
    cin >> n;
    a = vector<int>(n);
    for (auto &i: a) cin >> i, --i;
    SQ = sqrt(n) + 1;
    blck = vector<vector<int>>(SQ, vector<int>(2 * SQ + 2));
    ele = vector<vector<int>>(SQ, vector<int>(n));
    sz = vector<int>(SQ);
    for (int i = 0; i < n; ++i) {
        sz[i / SQ]++;
        blck[i / SQ][i % SQ] = a[i];
        ele[i / SQ][a[i]]++;
    }

    cin >> q;
    int lst{}, c{};
    while (q--) {
        int ty, l, r;
        cin >> ty >> l >> r;
        l = (l + lst - 1 + n) % n + 1;
        r = (r + lst - 1 + n) % n + 1;
        --l, --r;
        if (l > r) swap(l, r);
        if (ty == 1) {
            shift(l, r);
            c++;
        } else {
            int k;
            cin >> k;
            k = (k + lst - 1 + n) % n + 1;
            k--;
            lst = Query(l - 1, r, k);
            cout << lst << '\n';
        }

        if (c == SQ) build(), c = 0;
    }
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
