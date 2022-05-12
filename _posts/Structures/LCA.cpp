#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> ii;
const int MX = 40001;

vector<ii> g[MX];
int L[2 * MX], idx[MX], lev[MX];
int st[2 * MX][20], log[2 * MX];

int k = 0;
void dfs(int x, int l)
{
    L[++k] = x;
    lev[x] = l;
    idx[x] = k;
    for (int y : g[x])
    {
        if (lev[y]) continue;
        dfs(y, l + 1);
        L[++k] = x;
    }
}

int minLev(int u, int v)
{
    if (lev[u] < lev[v]) return u;
    return v;
}

void buildST()
{
    log[1] = 0;
    for (int i = 2; i <= k; i++) log[i] = log[i / 2] + 1;
    for (int i = 1; i <= k; i++) st[i][0] = L[i];
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) <= k; i++)
            st[i][j] = minLev(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int LCA(int u, int v)
{
    int l = idx[u], r = idx[v];
    if (l > r) swap(l, r);
    int j = log[r - l + 1];
    return minLev(st[l][j], st[r - (1 << j) + 1][j]);
}
