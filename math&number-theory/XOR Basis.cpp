// how many ways to construct x using xors = 2^(n-k), n is size of the vector space and k is the size of the basis
/* you have to at most iterate over the size of the size of the basis to check if there is an xor that equals zero 
    ex if B = 30 then you have to iterate at most 30
*/

const int B = 63;
struct Basis {
    int sz = 0;
    vector<int> b;

    Basis(): b(vector<int>(B)) {}

    void insert(int x) {
        for(int i = B - 1; ~i; --i) {
            if(!(x >> i & 1)) continue;
            if(!b[i]) {
                b[i] = x, ++sz;
                return;
            }
            x ^= b[i];
        }
    }

    bool can(int x) {
        for(int i = B - 1; ~i; --i) {
            if(!(x >> i & 1)) continue;
            if(!b[i]) return 0;
            x ^= b[i];
        }
        return !x;
    }

   int max_xor(int ans = 0) {
        for(int i = B - 1; i >= 0; i--) {
            ans = max(ans, ans ^ b[i]);
        }
        return ans;
    }
};

/* memory effient way
struct Basis {
    vector<int>b;
    int sz;
    Basis(){
        sz=0;
    }
    void insert(int x){
        for(auto y:b){
            x=min(x,x^y);
        }
        if(x){
            sz++;
            b.push_back(x);
        }
    }
    bool can(int x)
    {
        for(auto y:b){
            x=min(x,x^y);
        }
        return x==0;
    }
 
};
*/
