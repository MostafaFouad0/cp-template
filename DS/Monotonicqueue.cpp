class MonotonicQueue {
public:
    deque<ll> data;

    void push(ll x) {
        while (!data.empty() && data.back() < x)
            data.pop_back();
        data.push_back(x);
    }

    ll max() { return data.front(); }

    void pop(ll x) {
        if (!data.empty() && data.front() == x)
            data.pop_front();
    }
};
