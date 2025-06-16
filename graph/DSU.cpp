struct DSU
{
    vector<int> par;
    vector<int> siz;

    DSU(int size)
    {
        par = vector<int>(size);
        siz = vector<int>(size, 1);
        for (int i = 0; i < size; ++i)
        {
            par[i] = i;
        }
    }

    int find(int node)
    {
        if (par[node] == node)return node;
        return par[node] = find(par[node]); // merge 
    }

    void merge(int x, int y)
    {
        int leader1 = find(x);
        int leader2 = find(y);
        if (leader1 == leader2)return;
        if (siz[leader1] > siz[leader2])
        {
            siz[leader1] += siz[leader2];
            par[leader2] = leader1;
        }
        else
        {
            siz[leader2] += siz[leader1];
            par[leader1] = leader2;
        }
    }
};
