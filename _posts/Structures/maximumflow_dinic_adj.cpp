#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
using namespace std;
const int N = 502;
const int src = 0, snk = 501;

vector<int> g[N];
int c[N][N], f[N][N];
int lev[N];
int work[N];

bool bfs() {
    memset(lev, -1, sizeof lev);
    queue<int> q;
    q.push(src);
    lev[src] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : g[x]) {
            if (c[x][y] - f[x][y] > 0 && lev[y] == -1) {
                lev[y] = lev[x] + 1;
                q.push(y);
            }
        }
    }
    return lev[snk] != -1;
}

int dfs(int x, int flow) {
    if (x == snk) return flow;
    for (int &i = work[x]; i < g[x].size(); i++) {
        int y = g[x][i];
        if (c[x][y] - f[x][y] > 0 && lev[y] == lev[x] + 1) {
            int _f = dfs(y, min(flow, c[x][y] - f[x][y]));
            if (_f > 0) {
                f[x][y] += _f;
                f[y][x] -= _f;
                return _f;
            }
        }
    }
    return 0;
}

int max_flow() {
    int ans = 0;
    while (bfs()) {
        memset(work, 0, sizeof work);
        while (true) {
            int _f = dfs(src, 1e9);
            if (!_f) break;
            ans += _f;
        }
    }
    return ans;
}
