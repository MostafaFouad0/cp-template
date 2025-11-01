std::mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

struct item {
    int key, prior, cnt{};
    item *l, *r;

    item() {}

    item(int key) : key(key), cnt(1), prior(rand()), l(NULL), r(NULL) {}
};

typedef item *pitem;

void split(pitem t, int key, pitem &l, pitem &r) {
    if (!t)
        l = r = NULL;
    else if (t->key <= key)
        split(t->r, key, t->r, r), l = t;
    else
        split(t->l, key, l, t->l), r = t;
    if (l) l->cnt = (l->l ? l->l->cnt : 0) + (l->r ? l->r->cnt : 0) + 1;
    if (r) r->cnt = (r->l ? r->l->cnt : 0) + (r->r ? r->r->cnt : 0) + 1;
}

void insert(pitem &t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split(t, it->key, it->l, it->r), t = it;
    else
        insert(t->key <= it->key ? t->r : t->l, it);
    if (t) t->cnt = (t->l ? t->l->cnt : 0) + (t->r ? t->r->cnt : 0) + 1;
}

void merge(pitem &t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    if (t) t->cnt = (t->l ? t->l->cnt : 0) + (t->r ? t->r->cnt : 0) + 1;
}

void erase(pitem &t, int key) {
    if (t->key == key) {
        pitem th = t;
        merge(t, t->l, t->r);
        delete th;
    } else {
        erase(key < t->key ? t->l : t->r, key);
    }
    if (t) t->cnt = (t->l ? t->l->cnt : 0) + (t->r ? t->r->cnt : 0) + 1;
}

bool find(pitem t, int x) {
    if (!t) return false;
    if (t->key == x) return true;
    if (t->key < x) return find(t->r, x);
    return find(t->l, x);
}

int smallerorequal(pitem it, int x) {
    pitem l = NULL, r = NULL;
    split(it, x, l, r);
    int ret = (l ? l->cnt : 0);
    merge(it, l, r);
    return ret;
}

int kth(pitem it, int i) {
    int l = 1, r = (int) 1e9, md, ans = 0;
    while (l <= r) {
        md = l + r >> 1;
        (smallerorequal(it, md) < i ? ans = md, l = md + 1 : r = md - 1);
    }
    return ans + 1;
}
