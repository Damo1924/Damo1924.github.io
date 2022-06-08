#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct maxflow_dinic {
    struct edge {
        int to, c, f, rev;
    };
    
    int n, src, snk, ans = 0;
    vector<vector<edge>> g;
    vector<int> lev, work;
    
    maxflow_dinic(){}
    maxflow_dinic(int _n) : n(_n) {
        g.resize(_n); lev.resize(_n); work.resize(_n);
        src = 0, snk = _n - 1;
    }
    
    void add_edge(int s, int e, int c) {
        g[s].push_back({ e, c, 0, (int)g[e].size() });
        g[e].push_back({ s, 0, 0, (int)g[s].size() - 1 });
    }
    
    bool bfs() {
        fill(lev.begin(), lev.end(), -1);
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
    
    int dfs(int x, int flow) {
        if (x == snk) return flow;
        for (int &i = work[x]; i < g[x].size(); i++) {
            edge &e = g[x][i];
            if (e.c - e.f > 0 && lev[e.to] == lev[x] + 1) {
                int _f = dfs(e.to, min(flow, e.c - e.f));
                if (_f > 0) {
                    e.f += _f;
                    g[e.to][e.rev].f -= _f;
                    return _f;
                }
            }
        }
        return 0;
    }
    
    int maxflow() {
        int ans = 0;
        while (bfs()) {
            fill(work.begin(), work.end(), 0);
            while (true) {
                int _f = dfs(src, 1e9);
                if (!_f) break;
                ans += _f;
            }
        }
        return ans;
    }
};
