struct Segtree { // Sum segtree
    int n;
    vector<int> node, a;
    Segtree() {}
    Segtree(int _n) : n(_n) {
        node.resize(2 * n);
        a.resize(n);
    }
    void build() {
        for (int i = 0; i < n; i++) node[n + i] = a[i];
        for (int i = n - 1; i; i--) node[i] = node[2 * i] + node[2 * i + 1];
    }
    void upd(int idx, int val) {
        for (int i = n + idx; i; i /= 2) node[i] += val - a[idx];
        a[idx] = val;
    }
    int query(int l, int r) {
        l += n; r += n;
        int res = 0;
        while (l <= r) {
            if (l % 2 != 0) res += node[l++];
            if (r % 2 == 0) res += node[r--];
            l /= 2; r /= 2;
        }
        return res;
    }
};

// ----------------------

struct Segtree { // Max segtree
    int n;
    vector<int> node, a;
    Segtree() {}
    Segtree(int _n) : n(_n) {
        node.resize(2 * n);
        a.resize(n);
    }
    void build() {
        for (int i = 0; i < n; i++) node[n + i] = a[i];
        for (int i = n - 1; i; i--) node[i] = max(node[2 * i], node[2 * i + 1]);
    }
    int query(int l, int r) {
        l += n; r += n;
        int res = 0;
        while (l <= r) {
            if (l % 2 != 0) res = max(res, node[l++]);
            if (r % 2 == 0) res = max(res, node[r--]);
            l /= 2; r /= 2;
        }
        return res;
    }
};

//------------------

struct Segtree { // range update, element query
    int n;
    vector<int> node;
    Segtree() {}
    Segtree(int _n) : n(_n) { node.resize(2 * n); }
    void upd(int l, int r, int val) {
        l += n; r += n;
        while (l <= r) {
            if (l % 2 != 0) node[l++] += val;
            if (r % 2 == 0) node[r--] += val;
            l /= 2; r /= 2;
        }
    }
    int query(int idx) {
        int res = 0;
        for (int i = n + idx; i; i /= 2) res += node[i];
        return res;
    }
};
