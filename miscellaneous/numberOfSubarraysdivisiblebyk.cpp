 int count(vector<int>& a, int k) {
    map<int, int> mp;
    mp[0]++;
    int n=a.size();
    int tmp{};
    int ans{};
    for(int i=0;i<n;i++){
        tmp=(tmp+a[i]%k+k)%k;
        ans+=mp[tmp];
        mp[tmp]++;
    }
    return ans;
}
