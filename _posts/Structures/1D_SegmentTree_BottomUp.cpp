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

//-----------------

struct segtree_lazy {
    int n, h = 0;
    vector<ll> a, node, lazy;
    segtree_lazy() {}
    segtree_lazy(int _n) : n(_n) {
        for (int i = 1; i < n; i *= 2) h++;
        node.resize(2 * n);
        a.resize(n);
        lazy.resize(n);
    }
    void build() {
        for (int i = 0; i < n; i++) node[n + i] = a[i];
        for (int i = n - 1; i; i--) node[i] = node[i << 1] + node[i << 1 | 1];
    }
    void apply_node(int i, int len, ll val) { // lazy를 노드 i에 적용
        node[i] += len * val;
        if (i < n) lazy[i] += val;
    }
    void merge_node(int i, int len) { // 노드 i의 값 구하기
        if (i >= n) return;
        node[i] = node[i << 1] + node[i << 1 | 1] + len * lazy[i];
    }
    void prop(int i) { // lazy propagation
        for (int hh = h, len = 1 << h; hh > 0; --hh, len >>= 1) {
            int j = i >> hh;
            if (lazy[j]) {
                apply_node(j << 1, len >> 1, lazy[j]);
                apply_node(j << 1 | 1, len >> 1, lazy[j]);
                lazy[j] = 0;
            }
        }
    }
    void upd(int l, int r, ll val) {
        l += n; r += n;
        prop(l); prop(r);  
        for (int i = l, j = r, len = 1; i <= j; i >>= 1, j >>= 1, len <<= 1) {
            if (i & 1) apply_node(i++, len, val);
            if (!(j & 1)) apply_node(j--, len, val);
        }
        for (int i = l >> 1, len = 2; i; i >>= 1, len <<= 1) merge_node(i, len);
        for (int i = r >> 1, len = 2; i; i >>= 1, len <<= 1) merge_node(i, len);
    }
    ll query(int l, int r) {
        l += n; r += n;
        prop(l); prop(r);
        ll res = 0;
        while (l <= r) {
            if (l % 2 != 0) res += node[l++];
            if (r % 2 == 0) res += node[r--];
            l >>= 1; r >>= 1;
        }
        return res;
    }
};
