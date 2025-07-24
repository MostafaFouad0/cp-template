
//lpf : lowest prime divisor , gpf : greatest prime divisor, mob : mobius function u(n)
/* u(1) = 1,u(n) = 0 if n isnot free square number (has duplicate prime divisor),
u(n) = 1 if the number of prime diviosrs is even 
u(n) = -1 if the number of prime diviosrs is odd 
*/
vector<int> prime;
bitset<N> isComp;
int mob[N];
int lpf[N], gpf[N];
void sieve(int n = N) {
    isComp = 0;
    mob[1] = 1;
    for (int i = 2; i < n; ++i) {
        if (!isComp[i]) {
            prime.push_back(i);
            mob[i] = -1;
            lpf[i] = gpf[i] = i;
        }
        for (int j = 0; j < prime.size() && i * prime[j] < n; ++j) {
            isComp[i * prime[j]] = true;
            lpf[prime[j] * i] = prime[j];
            gpf[prime[j] * i] = gpf[i];
            if (i % prime[j] == 0) {
                mob[i * prime[j]] = 0;
                break;
            } else
                mob[i * prime[j]] = mob[i] * mob[prime[j]];
        }
    }
}
