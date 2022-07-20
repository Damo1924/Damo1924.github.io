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

//------------------------------------

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct Trie {
    int term;
    vector<pair<char, Trie*>> ch;
    Trie* fail;
    Trie() { term = 0; ch.clear(); fail = nullptr; }
    ~Trie() { for (auto& i : ch) delete i.second; }
    int idx(char c) {
        for (int i = 0; i < ch.size(); i++) if (ch[i].first == c) return i;
        return ch.size();
    }
    void insert(string& s, int i) {
        if (s.size() == i) {
            term = 1;
            return;
        }
        int j = idx(s[i]);
        if (j == ch.size()) ch.push_back({ s[i], new Trie });
        ch[j].second->insert(s, i + 1);
    }
    void init() {
        queue<Trie*> q;
        q.push(this);
        while (!q.empty()) {
            Trie* cur = q.front();
            q.pop();
            for (auto& i : cur->ch) {
                Trie* nxt = i.second;
                if (cur == this) nxt->fail = this;
                else {
                    Trie* tmp = cur->fail;
                    while (tmp != this && tmp->idx(i.first) == tmp->ch.size()) tmp = tmp->fail;
                    int j = tmp->idx(i.first);
                    if (j < tmp->ch.size()) tmp = tmp->ch[j].second;
                    nxt->fail = tmp;
                    if (tmp->term) nxt->term = 1;
                }
                q.push(nxt);
            }
        }
    }
    bool query(string& s) {
        Trie* cur = this;
        for (int i = 0; i < s.size(); i++) {
            while (cur != this && cur->idx(s[i]) == cur->ch.size()) cur = cur->fail;
            int j = cur->idx(s[i]);
            if (j < cur->ch.size()) cur = cur->ch[j].second;
            if (cur->term) return 1;
        }
        return 0;
    }
} aho_corasick;
