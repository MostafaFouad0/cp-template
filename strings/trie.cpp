struct Node
{
    int nxt[2];
    int freq;

    Node()
    {
        memset(nxt, -1, sizeof(nxt));
        freq = 0;
    }
};


vector<Node> trie;

void trie_add(int x)
{
    int idx{};
    for (int i = 29; i >= 0; i--)
    {
        bool bit = (x & (1 << i));
        if (trie[idx].nxt[bit] == -1)
	        trie[idx].nxt[bit] = trie.size(), trie.emplace_back();
        idx = trie[idx].nxt[bit];
        trie[idx].freq++;
    }
}

void trie_del(int x)
{
    int idx{};
    for (int i = 29; i >= 0; i--)
    {
        bool bit = (x & (1 << i));
        idx = trie[idx].nxt[bit];
        trie[idx].freq--;
    }
}
