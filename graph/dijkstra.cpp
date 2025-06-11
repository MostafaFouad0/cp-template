void dijkstra(int u) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, u});
    cost[u] = 0;
    while (!pq.empty()) {
        ll dis = pq.top().F;
        int cur = pq.top().S;
        pq.pop();
        if (dis != cost[cur])continue;
        for (auto child: adj[cur]) {
            if (cost[child.F] > dis + child.S) {
                cost[child.F] = dis + child.S;
                pq.push({dis + child.S, child.F});
            }
        }
    }
}
