#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct max_flow_edmondkarp {
    struct edge {
        int to, c, f, rev;
    };
    
    int n, src, snk;
    vector<vector<edge>> g;
    vector<int> path, idx;
    
    max_flow_edmondkarp(){}
    max_flow_edmondkarp(int _n) : n(_n) {
        g.resize(_n); path.resize(_n); idx.resize(_n);
        src = 0, snk = _n - 1;
    }
    
    void add_edge(int s, int e, int c) {
        g[s].push_back({ e, c, 0, (int)g[e].size() });
        g[e].push_back({ s, 0, 0, (int)g[s].size() - 1 });
    }
    
    int solve() {
        int ans = 0;
        while (true) {
            for (int i = 0; i < n; i++) path[i] = -1;
        
            queue<int> q;
            q.push(src);
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int i = 0; i < g[x].size(); i++) {
                    edge e = g[x][i];
                    if (e.c - e.f > 0 && path[e.to] == -1) {
                        q.push(e.to);
                        path[e.to] = x;
                        idx[e.to] = i;
                    }
                }
            }
            if (path[snk] == -1) break;
            
            int flow = 1e9;
            for (int i = snk; i != src; i = path[i])
                flow = min(flow, g[path[i]][idx[i]].c - g[path[i]][idx[i]].f);
            for (int i = snk; i != src; i = path[i]) {
                edge &e = g[path[i]][idx[i]];
                e.f += flow;
                g[i][e.rev].f -= flow;
            }
            ans += flow;
        }
        return ans;
    }
};
