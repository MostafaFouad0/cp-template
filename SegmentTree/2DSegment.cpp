#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define int long long
#define ll long long
using namespace std;

int const N = 1e5 + 1, M = 2e5 + 1;

vector<vector<int>> grid;

struct seg2d {
    vector<vector<int>> sg;
    int szx, szy;

    seg2d(int n, int m) {
        szx = szy = 1;
        while (szx < n) szx <<= 1;
        while (szy < m) szy <<= 1;
        sg = vector<vector<int>>(szx << 1, vector<int>(szy << 1));
    }

    void buildy(int &x, int &lx, int &rx, int y = 0, int ly = 0, int ry = -1) {
        if (!~ry) ry = szy - 1;
        if (ly == ry) {
            if (lx == rx) {
                if (ly < grid[0].size() and lx < grid.size()) sg[x][y] = grid[lx][ly];
            } else {
                sg[x][y] = sg[2 * x + 1][y] + sg[2 * x + 2][y];
            }
            return;
        }
        int md = ly + ry >> 1;
        buildy(x, lx, rx, 2 * y + 1, ly, md);
        buildy(x, lx, rx, 2 * y + 2, md + 1, ry);
        sg[x][y] = sg[x][2 * y + 1] + sg[x][2 * y + 2];
    }

    void buildx(int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = szx - 1;
        if (lx != rx) {
            int md = lx + rx >> 1;
            buildx(2 * x + 1, lx, md);
            buildx(2 * x + 2, md + 1, rx);
        }
        buildy(x, lx, rx);
    }

    int sumy(int l, int r, int &x, int y = 0, int ly = 0, int ry = -1) {
        if (!~ry) ry = szy - 1;
        if (r < ly or ry < l) return 0;
        if (l <= ly and ry <= r) return sg[x][y];
        int md = ly + ry >> 1;
        return sumy(l, r, x, 2 * y + 1, ly, md) + sumy(l, r, x, 2 * y + 2, md + 1, ry);
    }

    int sumx(int lx, int rx, int ly, int ry, int x = 0, int l = 0, int r = -1) {
        if (!~r) r = szx - 1;
        if (rx < l or r < lx) return 0;
        if (lx <= l and r <= rx) return sumy(ly, ry, x);
        int md = l + r >> 1;
        return sumx(lx, rx, ly, ry, 2 * x + 1, l, md) + sumx(lx, rx, ly, ry, 2 * x + 2, md + 1, r);
    }

    void updatey(int posx, int posy, int val, int &x, int &lx, int &rx, int y = 0, int ly = 0, int ry = -1) {
        if (!~ry) ry = szy - 1;
        if (ly == ry) {
            if (lx == rx) sg[x][y] = val;
            else sg[x][y] = sg[2 * x + 1][y] + sg[2 * x + 2][y];
            return;
        }
        int md = ly + ry >> 1;
        if (posy <= md) updatey(posx, posy, val, x, lx, rx, 2 * y + 1, ly, md);
        else updatey(posx, posy, val, x, lx, rx, 2 * y + 2, md + 1, ry);
        sg[x][y] = sg[x][2 * y + 1] + sg[x][2 * y + 2];
    }

    void updatex(int posx, int posy, int val, int x = 0, int lx = 0, int rx = -1) {
        if (!~rx) rx = szx - 1;
        if (lx != rx) {
            int md = lx + rx >> 1;
            if (posx <= md) updatex(posx, posy, val, 2 * x + 1, lx, md);
            else updatex(posx, posy, val, 2 * x + 2, md + 1, rx);
        }
        updatey(posx, posy, val, x, lx, rx);
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
        }
    }

    sg.buildx();
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, y;
            cin >> x >> y;
            --y, --x;
            sg.updatex(x, y, grid[x][y] ^ 1);
            grid[x][y] ^= 1;
        } else {
            int ly, lx, ry, rx;
            cin >> lx >> ly >> rx >> ry;
            --ly, --lx, --ry, --rx;
            cout << sg.sumx(lx, rx, ly, ry) << '\n';
        }
    }
}
