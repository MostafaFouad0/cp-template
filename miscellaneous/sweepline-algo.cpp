bool comp(pair<int,int>& a, pair<int,int>& b)
{
    if (a.F < b.F)return true;
    if (a.F == b.F)return a.S > b.S;
    return false;
}


int SweepLine(vector<pair<int,int>>& a)
{
    vector<pair<int,int>> pairs;
    int ret{};
    for (auto& [l,r] : a)
    {
        pairs.push_back({l, 1});
        pairs.push_back({r, -1});
    }
    sort(pairs.begin(), pairs.end(), comp);
    int sum{};
    for (auto& [time,delta] : pairs)
    {
        sum += delta;
        ret = max(ret, sum);
    }
    return ret; // maximum number of intersections in a single point
}
