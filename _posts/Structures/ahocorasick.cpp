#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

const int mxN = 1e5 + 1, mxC = 26;
struct aho_corasick {
    int trie[mxN][mxC], piv = 0;
    int fail[mxN];
    int term[mxN];
    
    void init(vector<string> &v) {
        memset(trie, 0, sizeof(trie));
        memset(fail, 0, sizeof(fail));
        memset(term, 0, sizeof(term));
        piv = 0;
        
        for (string &s : v) {
            int p = 0;
            for (int i = 0; i < s.size(); i++) {
                int j = s[i] - 'a';
                if (!trie[p][j]) trie[p][j] = ++piv;
                p = trie[p][j];
            }
            term[p] = 1;
        }
        
        queue<int> q;
        for (int i = 0; i < mxC; i++) if (trie[0][i]) q.push(trie[0][i]);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < mxC; i++) if (trie[x][i]) {
                int p = fail[x];
                while (p && !trie[p][i]) p = fail[p];
                p = trie[p][i];
                fail[trie[x][i]] = p;
                if (term[p]) term[trie[x][i]] = 1;
                q.push(trie[x][i]);
            }
        }
    }
    
    bool query(string& s) {
        int p = 0;
        for (int i = 0; i < s.size(); i++) {
            int j = s[i] - 'a';
            while (p && !trie[p][j]) p = fail[p];
            p = trie[p][j];
            if (term[p]) return 1;
        }
        return 0;
    }
};
