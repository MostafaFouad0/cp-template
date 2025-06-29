struct Node
{
    map<char,int> ch;
    int freq{};
    int& operator[](const char x)
    {
        return ch[x];
    }

    Node()
    {
    };
};

struct Trie
{
    vector<Node> trie;
    int newNode()
    {
        trie.emplace_back();
        return trie.size() - 1;
    }

    Trie()
    {
        newNode();
    }

    void clear()
    {
        trie.clear();
        newNode();
    }

    void add(const string& s)
    {
        int idx{};
        for (const auto it : s)
        {
            if (!trie[idx][it])trie[idx][it] = newNode();
            idx = trie[idx][it];
            trie[idx].freq++;
        }
    }

    int query(const string& s)
    {
        int idx{};
        for (const auto it : s)
        {
            if (!trie[idx][it])return 0;
            idx = trie[idx][it];
        }
        return trie[idx].freq;
    }
};
