#include <bits/stdc++.h>

#define Pc_champs ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);

#define int long long
#define ll long long
using namespace std;
int const N = 2e5 + 5, N2 = 1e3 + 1, M = 1e9 + 7, SQ = 317, LOG = 19;
const int MAXD = 2;

inline int64_t sq(int x) { return x * 1ll * x; }

struct point {
    int c[MAXD];

    point() {}
};

struct cmp {
    int current_d;

    cmp() { current_d = 0; }

    cmp(int d) { current_d = d; }

    bool operator()(const point &a, const point &b) { return a.c[current_d] < b.c[current_d]; }
};

int64_t sq_dist(point a, point b, int d) {
    int64_t answer = 0;
    for (int i = 0; i < d; i++)
        answer += sq(a.c[i] - b.c[i]);

    return answer;
}

int man_dist(point a, point b, int d) {
    int64_t answer = 0;
    for (int i = 0; i < d; i++)
        answer += abs(a.c[i] - b.c[i]);

    return answer;
}

struct kd_tree {
    struct node {
        point p;
        int L, R, axis;

        node() {
            L = -1;
            R = -1;
        }

        node(point _p) {
            L = -1;
            R = -1;
            p = _p;
        }
    };

    int psz = 0, D, root;
    vector<node> tr;

    kd_tree() {
        D = 0;
        psz = 0;
    }

    kd_tree(int n, int d) {//n points - dimension
        D = d;
        psz = 0;
        tr = vector<node>(n << 2);
    }

    int new_node() { return psz++; }

    int build(point *from, point *to, int axis) {
        if (to - from == 0)
            return -1;

        point *mid = from + (to - from) / 2;

        nth_element(from, mid, to, cmp(axis));

        int c_node = new_node();
        tr[c_node] = node(*mid);

        tr[c_node].axis = axis;

        tr[c_node].L = build(from, mid, (axis + 1) % D);
        tr[c_node].R = build(mid + 1, to, (axis + 1) % D);

        return c_node;
    }

    void init(point *from, point *to, int d) {
        D = d;
        random_shuffle(from, to);
        root = build(from, to, 0);
    }

    int cntt, mn;

    void query(int idx, point q, int64_t answer) {
        if (idx == -1) return;
        int ttt = sq_dist(q, tr[idx].p, D);
        int dis = man_dist(q, tr[idx].p, D);
        if (dis) mn = min(mn, dis); //it can get the same point so be careful
        if (ttt <= answer)cntt++;
        if (tr[idx].p.c[tr[idx].axis] <= q.c[tr[idx].axis]) {
            query(tr[idx].R, q, answer);
            if (tr[idx].L != -1 && q.c[tr[idx].axis] - sqrt(answer) <= tr[idx].p.c[tr[idx].axis])
                query(tr[idx].L, q, answer);
        } else {
            query(tr[idx].L, q, answer);
            if (tr[idx].R != -1 && q.c[tr[idx].axis] + sqrt(answer) >= tr[idx].p.c[tr[idx].axis])
                query(tr[idx].R, q, answer);
        }
    }

    void query(int idx, point q) {
        if (idx == -1) return;
        int dis = man_dist(q, tr[idx].p, D);
        if (dis) mn = min(mn, dis); //it can get the same point so be careful
        if (tr[idx].p.c[tr[idx].axis] <= q.c[tr[idx].axis]) {
            query(tr[idx].R, q);
            if (tr[idx].L != -1 && q.c[tr[idx].axis] - mn <= tr[idx].p.c[tr[idx].axis])
                query(tr[idx].L, q);
        } else {
            query(tr[idx].L, q);
            if (tr[idx].R != -1 && q.c[tr[idx].axis] + mn >= tr[idx].p.c[tr[idx].axis])
                query(tr[idx].R, q);
        }
    }

    int inCircle(point q, int rad) {
        cntt = 0;
        query(root, q, rad * rad);
        return cntt;
    }

    int minDistance(point p) {
        mn = (int) 1e15;
        query(root, p);
        return mn;
    }

    void U(int idx, point q, int axis) {
        if (tr[idx].p.c[tr[idx].axis] <= q.c[tr[idx].axis]) {
            if (tr[idx].R == -1) {
                int c_node = new_node();
                tr[c_node] = node(q);

                tr[c_node].axis = axis;
                tr[idx].R = c_node;
            } else
                U(tr[idx].R, q, (axis + 1) % D);
        } else {
            if (tr[idx].L == -1) {
                int c_node = new_node();
                tr[c_node] = node(q);

                tr[c_node].axis = axis;
                tr[idx].L = c_node;
            } else
                U(tr[idx].L, q, (axis + 1) % D);
        }
    }

    void update(point q) {
        U(root, q, 0);
    }
};

int d = 2;
point li[N], ori[N];
kd_tree kd;

int n, q, idx;

void dowork() {
    cin >> n;
    map<pair<int, int>, int> mp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            cin >> li[i].c[j];
        }
        ori[i] = li[i];
        mp[{li[i].c[0], li[i].c[1]}]++;
    }

    kd = kd_tree(n + 1, d);
    kd.init(li, li + n, d);

    for (int i = 0; i < n; ++i) {
        if (mp[{ori[i].c[0], ori[i].c[1]}] > 1) cout << "0\n";
        cout << kd.minDistance(ori[i]) << '\n';
    }
}
