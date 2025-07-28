struct Node {
    Node *link[2];
    int cnt{};
};

struct Trie {
    Node *root;

    Trie() {
        root = new Node();
    }

    void insert(string &s) {
        Node *node = root;
        for (char &i: s) {
            i -= '0';
            if (node->link[i] == NULL) node->link[i] = new Node();
            node = node->link[i];
            node->cnt++;
        }
    }
};
