vector<vector<pair<int, int>>> adj;
void dijk(int st) {
    int cost[N];
    memset(cost, '?', sizeof cost);
    set<pair<int, int>> pq;
    pq.insert({0, st});
    cost[st] = 0;
    while (!pq.empty()) {
        int cst = pq.begin()->first, node = pq.begin()->second;
        pq.erase(pq.begin());
        if (cst > cost[node]) continue;
        for (auto i: adj[node]) {
            if (i.second + cst < cost[i.first]) {
                pq.erase({cost[i.first], i.first});
                pq.insert({cost[i.first] = i.second + cst, i.first});
            }
        }
    }
}
