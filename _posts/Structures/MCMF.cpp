struct MCMF {
    struct edge {
        int to, f, mxF, c; // to: 간선의 끝점, f: 흐르는 유량, mxF: 흐를 수 있는 최대 유량, c: 비용
        edge *rev; // 반대방향 간선
        
        edge(){}
        edge(int _to, int _mxF, int _c) { to = _to, f = 0, mxF = _mxF, c = _c, rev = nullptr; }
        
        int canFlow() { return mxF - f; }
        void addFlow(int f1) { f += f1, rev->f -= f1; }
    };
    
    int n; // number of vertex
    vector<vector<edge*>> adj; // graph
    
    MCMF(int _n): n(_n) { adj.resize(_n); }
    
    void addEdge(int u, int v, int mxF, int c) {
        edge *e1 = new edge(v, mxF, c);
        edge *e2 = new edge(u, 0, -c);
        e1->rev = e2;
        e2->rev = e1;
        adj[u].push_back(e1);
        adj[v].push_back(e2);
    }
    ll solve(const int src, const int snk) { // using SPFA
        ll ret = 0;
        while (true) {
            vector<int> par(n, -1);
            vector<ll> dist(n, 1e18);
            vector<bool> inQ(n, 0);
            vector<edge*> path(n, nullptr);
            
            queue<int> q;
            q.push(src);
            dist[src] = 0;
            inQ[src] = 1;
            while (!q.empty())
            {
                int cur = q.front();
                q.pop();
                inQ[cur] = 0;
                
                for (edge *e : adj[cur]) {
                    int nxt = e->to;
                    if (e->canFlow() > 0 && dist[nxt] > dist[cur] + e->c) {
                        dist[nxt] = dist[cur] + e->c;
                        par[nxt] = cur;
                        path[nxt] = e;
                        if (!inQ[nxt]) {
                            q.push(nxt);
                            inQ[nxt] = 1;
                        }
                    }
                }
            }
            if (par[snk] == -1) break;
            
            int mnF = 1e9;
            for (int i = snk; i != src; i = par[i]) mnF = min(mnF, path[i]->canFlow());
            for (int i = snk; i != src; i = par[i]) {
                path[i]->addFlow(mnF);
                ret += 1ll * mnF * path[i]->c;
            }
        }
        return ret;
    }
};
