#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct max_flow_dinic {
    struct edge {
        int to, c, f, rev;
    };
    
    int n, src, snk, ans = 0;
    vector<vector<edge>> g;
    vector<int> lev, path, idx;
    
    max_flow_dinic(){}
    max_flow_dinic(int _n) : n(_n) {
        g.resize(_n); lev.resize(_n); path.resize(_n); idx.resize(_n);
        src = 0, snk = _n - 1;
    }
    
    void add_edge(int s, int e, int c) {
        g[s].push_back({ e, c, 0, (int)g[e].size() });
        g[e].push_back({ s, 0, 0, (int)g[s].size() - 1 });
    }
    
    bool bfs() {
        for (int i = 0; i < n; i++) lev[i] = -1;
        queue<int> q;
        q.push(src);
        lev[src] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (edge e : g[x]) {
                if (e.c - e.f > 0 && lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return lev[snk] != -1;
    }
    
    bool dfs(int x, int flow) {
        if (x == snk) {
            for (int i = snk; i != src; i = path[i]) {
                edge &e = g[path[i]][idx[i]];
                e.f += flow;
                g[i][e.rev].f -= flow;
            }
            ans += flow;
            return true;
        }
        
        for (int i = 0; i < g[x].size(); i++) {
            edge e = g[x][i];
            if (e.c - e.f > 0 && lev[e.to] == lev[x] + 1) {
                path[e.to] = x;
                idx[e.to] = i;
                if (dfs(e.to, min(flow, e.c - e.f))) return true;
            }
        }
        return false;
    }
    
    void solve() {
        while (bfs())
            while (dfs(src, 1e9));
    }
};
