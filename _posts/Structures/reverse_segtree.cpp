// 구간 업데이트 쿼리와 단일원소의 값을 반환하는 쿼리를 log N 으로 처리할 수 있는 세그트리
// sum(idx) : a[idx] 의 값 반환.
// upd(l, r, dif) : a[l] ~ a[r] 에 dif 를 더함.

struct reverse_Segtree
{
    int n;
    vector<int> node, a;
    
    reverse_Segtree() {}
    reverse_Segtree(int _n) : n(_n)
    {
        node.resize(2 * n);
        a.resize(n);
    }
    
    int sum(int idx)
    {
        int res = a[idx];
        for (int i = n + idx; i; i /= 2) res += node[i];
        return res;
    }
    
    void upd(int l, int r, int dif)
    {
        l += n, r += n;
        while (l <= r)
        {
            if (l % 2 != 0) node[l++] += dif;
            if (r % 2 == 0) node[r--] += dif;
            l /= 2; r /= 2;
        }
    }
};
