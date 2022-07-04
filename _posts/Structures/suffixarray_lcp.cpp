#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> suffix_array(string& s) {
    int n = s.size(), m = max(256, n) + 1;
    vector<int> sa(n), r(2 * n, 0), nr(n, 0), cnt(m), idx(n);
    
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        r[i] = s[i];
    }
    int rank = 1;
    for (int d = 1; d < n; d *= 2) {
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[r[i + d]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) idx[--cnt[r[i + d]]] = i;
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[r[i]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[r[idx[i]]]] = idx[i];
        
        if (rank == n) break;
        rank = 1; nr[sa[0]] = 1;
        for (int i = 1; i < n; i++) {
            if (r[sa[i - 1]] < r[sa[i]] || r[sa[i - 1] + d] < r[sa[i] + d]) rank++;
            nr[sa[i]] = rank;
        }
        for (int i = 0; i < n; i++) r[i] = nr[i];
    }
    return sa;
}

vector<int> LCP(string& s) {
    int n = s.size();
    vector<int> sa = suffix_array(s), lcp(n), r(n);
    for (int i = 0; i < n; i++) r[sa[i]] = i;
    
    int k = 0;
    for (int p = 0; p < n; p++) {
        if (r[p] == 0) continue;
        
        int q = sa[r[p] - 1];
        while (p + k < n && q + k < n && s[p + k] == s[q + k]) k++;
        lcp[r[p]] = (k > 0) ? k-- : 0;
    }
    return lcp;
}
