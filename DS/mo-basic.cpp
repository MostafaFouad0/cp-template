/// lx=0,rx=-1
struct MO
{
    int l, r, idx;

    MO(int l, int r, int idx) : l(l), r(r), idx(idx)
    {
    }

    MO()
    {
    }

    bool operator<(MO right)
    {
        if (this->l / root != right.l / root)
        {
            return this->l / root < right.l / root;
        }
        return this->r < right.r;
    }
};

vector<MO> qu;

void add(int idx)
{
	// update this
}

void remove(int idx)
{
	// update this
}

void query(int l, int r)
{
		// add then remove
    while (rx < r)add(++rx);
    while (lx > l)add(--lx);
    while (lx < l)del(lx++);
    while (rx > r)del(rx--);
}
