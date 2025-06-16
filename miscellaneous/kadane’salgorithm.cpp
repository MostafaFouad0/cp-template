long long maxSubarraySum(int arr[], int n) {
    long long maxi = LONG_MIN;
    long long sum{};
    int start{};
    int ansStart = -1, ansEnd = -1;
    for (int i = 0; i < n; i++) {
        if (sum == 0) start = i; // starting index
        sum += arr[i];
        if (sum > maxi) {
            maxi = sum;
            ansStart = start;
            ansEnd = i;
        }
        if (sum < 0) {
            sum = 0;
        }
    }
    return maxi;
}
