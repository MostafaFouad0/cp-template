int Longest_Subarray_with_Sum_equal_to_K(vector<int> &a, int k) {
    int n = arr.size();
    map<int, int> m;
    m[0] = 0;
    int ans = 0, s = 0;
    for (int i = 1; i <= n; ++i) {
        s += a[i];
        int rem = s - k;
        if (m.count(rem)) 
        {
            ans = max(ret, i - m[rem]);
        }
        if (m.count(s) == 0)
        {
          m[s] = i;
        }
    }
    return ans;
}
