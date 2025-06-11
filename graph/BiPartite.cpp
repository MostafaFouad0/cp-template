vector<vector<int>> adj;
vector<int> col;

bool isBipartite() {
    bool isbipartite = 1;
    for (int i = 1; i <= n; ++i) {
        if (col[i] == -1) {
            col[i] = 0;
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int p = q.front();
                q.pop();
                for (auto j: adj[p]) {
                    if (col[j] == -1) {
                        col[j] = col[p] ^ 1;
                        q.push(j);
                    } else {
                        isbipartite &= (col[j] != col[p]);
                    }
                }
            }
        }
    }
    return isbipartite;
}
