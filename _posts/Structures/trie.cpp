#include <vector>
#include <map>
using namespace std;

struct Trie {
    bool end;
    map<char, Trie*> ch;
    Trie() { end = 0; ch.clear(); }
    void insert(string& s, int i) {
        if (s.size() == i) {
            end = 1;
            return;
        }
        if (!ch.count(s[i])) ch[s[i]] = new Trie;
        ch[s[i]]->insert(s, i + 1);
    }
    bool find(string& s, int i) {
        if (s.size() == i) return end;
        if (!ch.count(s[i])) return 0;
        return ch[s[i]]->find(s, i + 1);
    }
};
