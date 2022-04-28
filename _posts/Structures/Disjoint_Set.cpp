struct disjoint_set {
    vector<int> par;
    
    disjoint_set() {};
    disjoint_set(int n) : par(n, -1) {}
    
    int find(int u)
    {
        if (par[u] < 0) return u;
        return par[u] = find(par[u]);
    }

    bool merge(int u, int v)
    {
        u = find(u); v = find(v);
        if (u == v) return false;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
};
