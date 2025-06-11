std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());

ll rand(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

struct PermutationHash {
    ll a, b, c, d;

    PermutationHash(ll a, ll b, ll c, ll d) : a(a), b(b), c(c), d(d) {}

    PermutationHash() {
        a = rand(1, 1e9);
        b = rand(1, 1e9);
        c = rand(1, 1e9);
        d = rand(1, 1e9);
    }

    PermutationHash operator+(PermutationHash tmp) {
        return PermutationHash(a + tmp.a, b + tmp.b, c + tmp.c, d + tmp.d);
    }

    PermutationHash operator-(PermutationHash tmp) {
        return PermutationHash(a - tmp.a, b - tmp.b, c - tmp.c, d - tmp.d);
    }

    bool operator==(PermutationHash tmp) {
        return a == tmp.a and b == tmp.b and c == tmp.c and d == tmp.d;
    }

    bool operator<(const PermutationHash &tmp) const {
        return tie(a, b, c, d) < tie(tmp.a, tmp.b, tmp.c, tmp.d);
    }
};
