bool cmp(int a, int b) {
    return lvl[a] > lvl[b];
}
 
array<int, 2> intersect(array<int, 2> p1, array<int, 2> p2) {
    vector<int> v;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            v.emplace_back(LCA(p1[i], p2[j]));
        }
    }
    sort(v.begin(), v.end(), cmp);
    if (v[0] == v[1])
        if (lvl[v[0]] < max(lvl[LCA(p1[0], p1[1])], lvl[LCA(p2[0], p2[1])]))
            return {0, 0};
    return {v[0], v[1]};
}
