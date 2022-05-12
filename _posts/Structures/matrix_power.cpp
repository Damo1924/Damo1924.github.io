// matrixMul: a = a * b
// matrixPow: a = b ^ p

void matrixMul(int n, vector<vector<ll>>& a, vector<vector<ll>>& b)
{
    vector<vector<ll>> tmp(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                tmp[i][j] += a[i][k] * b[k][j];
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = tmp[i][j] % MOD;
}

void matrixPow(int n, vector<vector<ll>>& a, vector<vector<ll>> b, int p)
{
    if (p == 1) return;
    matrixPow(n, a, b, p / 2);
    matrixMul(n, a, a);
    if (p % 2) matrixMul(n, a, b);
}
