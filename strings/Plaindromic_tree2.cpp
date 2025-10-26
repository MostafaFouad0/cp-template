#include <bits/stdc++.h>
using namespace std;
 
struct PalindromicTree {
    struct Node {
        int len, link;
        map<char, int> next;
        Node(int _len = 0) : len(_len), link(0) {}
    };
 
    string s;
    vector<Node> tree;
    int suff;
    int distinct_count;
 
    PalindromicTree(int n = 0) {
        tree.reserve(n + 5);
        tree.emplace_back(-1);
        tree.emplace_back(0);
        tree[0].link = 0;
        tree[1].link = 0;
        suff = 1;
        distinct_count = 0;
    }
 
    stack<pair<int*, int>> st;
    void add(char c) {
        s += c;
        int pos = (int)s.size() - 1;
        int cur = suff;
 
        while (true) {
            int curLen = tree[cur].len;
            if(pos - curLen - 1 >= 0 && s[pos - curLen - 1] == c) break;
            cur = tree[cur].link;
        }
 
        if (tree[cur].next.count(c) && ~tree[cur].next[c]) {
            st.emplace(&suff, suff);
            suff = tree[cur].next[c];
            return;
        }
 
        int now = int(tree.size());
        st.emplace(nullptr, 0);
        tree.emplace_back(tree[cur].len + 2);
        tree[cur].next.emplace(c, -1);
        st.emplace(&tree[cur].next[c], tree[cur].next[c]);
        tree[cur].next[c] = now;
 
        if (tree[now].len == 1) {
            tree[now].link = 1;
        } else {
            while (true) {
                cur = tree[cur].link;
                int curLen = tree[cur].len;
                if (pos - curLen - 1 >= 0 && s[pos - curLen - 1] == c) {
                    tree[now].link = tree[cur].next[c];
                    break;
                }
            }
        }
 
        st.emplace(&suff, suff);
        suff = now;
        st.emplace(&distinct_count, distinct_count);
        distinct_count++;
    }
 
    int shot() {
        return int(st.size());
    }
    void rollback(int sh) {
        s.pop_back();
        while(sh < st.size()) {
            if(st.top().first)
                *st.top().first = st.top().second;
            else
                tree.pop_back();
            st.pop();
        }
    }
 
    int dis() { return distinct_count; }
};
 
const int N = 3e7 + 1;
int pc, prm[1857859], phi[N];
 
auto pre_Sieve = []() {
    phi[1] = 1;
    for (int i = 2; i < N; i++){
        if(!phi[i]) prm[pc++] = i, phi[i] = i - 1;
        for(int j = 0; i * prm[j] < N; j++) {
            if(i % prm[j] == 0) {
                phi[i * prm[j]] = prm[j] * phi[i];
                break;
            }
            phi[i * prm[j]] = (prm[j] - 1) * phi[i];
        }
    }
    return 0;
}();
 
void TC() {
    int q;
    cin >> q;
    PalindromicTree pt(q * 2);
    stack<int> mem;
    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int x;
            cin >> x;
            int f = phi[x + pt.s.size()] % 26 + 1;
            mem.push(pt.shot());
            pt.add(char(f + 'a'));
        }
        else if(t == 2) {
            if(!mem.empty()) {
                pt.rollback(mem.top());
                mem.pop();
            }
        }
        else {
            cout << pt.dis() << '\n';
        }
    }
}
 
int32_t main() {
//    const int n = 1e5;
//    vector<int> a; a.reserve(n);
//    auto it = a.begin();
//    for(int i = 0; i < n; i++) {
//        a.push_back(i);
//        assert(it == a.begin());
//    }
//    for(int i = 0; i < n; i++) {
//        a.pop_back();
//        assert(it == a.begin());
//    }
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = 1;
    cin >> tc;
    for (int test = 1; test <= tc; ++test) {
        TC();
    }
    cerr << clock() / 1000.0 << " Secs";
    return 0;
}
