struct DSU {
    vector<int> parent, GroupSize;

    DSU(int size) {
        parent = GroupSize = vector<int>(size + 1);
        for (int i = 1; i <= size; ++i) {
            parent[i] = i;
            GroupSize[i] = 1;
        }
    }

    int FindLeader(int node) {
        if (parent[node] == node)return node;
        return parent[node] = FindLeader(parent[node]);
    }

    bool SameGroup(int u, int v) {
        int leader1 = FindLeader(u);
        int leader2 = FindLeader(v);
        return leader1 == leader2;
    }

    int GetSize(int node) {
        int leader = FindLeader(node);
        return GroupSize[leader];
    }

    void MergeGroups(int u, int v) {
        int leader1 = FindLeader(u);
        int leader2 = FindLeader(v);
        if (leader1 == leader2)return;
        if (GroupSize[leader1] > GroupSize[leader2]) {
            parent[leader2] = leader1;
            GroupSize[leader1] += GroupSize[leader2];
            return;
        }
        parent[leader1] = leader2;
        GroupSize[leader2] += GroupSize[leader1];

    }

};
