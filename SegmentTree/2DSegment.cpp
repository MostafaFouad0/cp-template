#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define int long long
#define ll long long
using namespace std;

int const N = 1e5 + 1, M = 2e5 + 1;

vector<vector<int>> grid;

struct seg2d {
    int n, m;
    vector<vector<int>> seg;

    int merge(int a, int b) const {
        return a + b;
    }

    seg2d(int n, int m) : n(n), m(m) {
        seg = vector<vector<int>>(2 * n,
                                  vector<int>(2 * m, 0));
    }

    int qry(int x1, int y1, int x2, int y2) const {
        int ret = 0;
        int y3 = y1 + m, y4 = y2 + m;
        for (x1 += n, x2 += n; x1 <= x2; ++x1 /= 2,
                --x2 /= 2) {
            for (y1 = y3, y2 = y4; y1 <= y2; ++y1 /= 2,
                    --y2 /= 2) {
                if ((x1 & 1) and (y1 & 1))
                    ret = merge(ret, seg[x1][y1]);
                if ((x1 & 1) and !(y2 & 1))
                    ret = merge(ret, seg[x1][y2]);
                if (!(x2 & 1) and (y1 & 1))
                    ret = merge(ret, seg[x2][y1]);
                if (!(x2 & 1) and !(y2 & 1))
                    ret = merge(ret, seg[x2][y2]);
            }
        }
        return ret;
    }

    void upd(int x, int y, int val) {
        int y2 = y += m;
        for (x += n; x; x /= 2, y = y2) {
            if (x >= n) seg[x][y] = val;
            else
                seg[x][y] = merge(
                        seg[2 * x][y], seg[2 * x + 1][y]);
            while (y /= 2)
                seg[x][y] = merge(seg[x][2 * y],
                                  seg[x][2 * y + 1]);
        }
    }
};

int n, q, idx;

void dowork() {
    cin >> n >> q;
    seg2d sg = seg2d(n, n);
    grid = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char x;
            cin >> x;
            grid[i][j] = (x == '*');
            sg.upd(i, j, (x == '*'));
        }
    }

    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, y;
            cin >> x >> y;
            --y, --x;
            grid[x][y] ^= 1;
            sg.upd(x, y, grid[x][y]);
        } else {
            int ly, lx, ry, rx;
            cin >> lx >> ly >> rx >> ry;
            --ly, --lx, --ry, --rx;
            cout << sg.qry(lx, ly, rx, ry) << '\n';
        }
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
        ++idx;
        dowork();
        cout << '\n';
    }
}
