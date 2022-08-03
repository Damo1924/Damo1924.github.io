struct fenwick {
    int n;
    vector<ll> a, node;
    fenwick(int _n): n(_n) {
        a.resize(n + 1);
        node.resize(n + 1);
    }
    void upd(int i, int val) {
        ll diff = val - a[i];
        while (i <= n) {
            node[i] += diff;
            i += (i & -i);
        }
        a[i] = val;
    }
    ll sum(int i) {
        ll res = 0;
        while (i) {
            res += node[i];
            i &= i - 1;
        }
        return res;
    }
    ll sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
