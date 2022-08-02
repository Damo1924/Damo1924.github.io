struct segtree {
    int n;
    vector<ll> a, node;
    segtree() {}
    segtree(int _n) : n(_n) {
        a.resize(n + 1);
        int h = (int)ceil(log2(n));
        node.resize(1 << (h + 1));
    }
    ll build(int u, int s, int e) {
        if (s == e) return node[u] = a[s];
        int m = (s + e) / 2;
        return node[u] = build(2 * u, s, m) + build(2 * u + 1, m + 1, e);
    }
    void upd(int u, int s, int e, int i, int diff) {
        if (i < s || e < i) return;
        node[u] += diff;
        if (s == e) return;
        int m = (s + e) / 2;
        upd(2 * u, s, m, i, diff);
        upd(2 * u + 1, m + 1, e, i, diff);
    }
    ll query(int u, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return node[u];
        int m = (s + e) / 2;
        return query(2 * u, s, m, l, r) + query(2 * u + 1, m + 1, e, l, r);
    }
};

//-----------------

struct segtree_lazy {
    int n;
    vector<ll> a, node, lazy;
    segtree_lazy() {}
    segtree_lazy(int _n) : n(_n) {
        a.resize(n + 1);
        int h = (int)ceil(log2(n));
        node.resize(1 << (h + 1));
        lazy.resize(1 << (h + 1));
    }
    ll build(int u, int s, int e) {
        if (s == e) return node[u] = a[s];
        int m = (s + e) / 2;
        return node[u] = build(2 * u, s, m) + build(2 * u + 1, m + 1, e);
    }
    void lazy_propagation(int u, int s, int e) {
        node[u] += (e - s + 1) * lazy[u];
        if (s != e) {
            lazy[2 * u] += lazy[u];
            lazy[2 * u + 1] += lazy[u];
        }
        lazy[u] = 0;
    }
    void upd(int u, int s, int e, int l, int r, ll diff) {
        if (lazy[u]) lazy_propagation(u, s, e);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lazy[u] = diff;
            lazy_propagation(u, s, e);
            return;
        }
        int m = (s + e) / 2;
        upd(2 * u, s, m, l, r, diff);
        upd(2 * u + 1, m + 1, e, l, r, diff);
        node[u] = node[2 * u] + node[2 * u + 1];
    }
    ll query(int u, int s, int e, int l, int r) {
        if (lazy[u]) lazy_propagation(u, s, e);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return node[u];
        int m = (s + e) / 2;
        return query(2 * u, s, m, l, r) + query(2 * u + 1, m + 1, e, l, r);
    }
};
