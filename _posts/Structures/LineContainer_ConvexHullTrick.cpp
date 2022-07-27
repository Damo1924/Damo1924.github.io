#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;
typedef long long ll;

struct Line {
    ll a, b, p; // y = ax + b, x = p
    bool operator<(const Line& l) const { return p < l.p; }
};
struct LineContainer : vector<Line> {
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    void add(ll a, ll b) {
        if (empty()) {
            push_back({ a, b, 0 });
            return;
        }
        while (true) {
            Line prv = back();
            ll p = div(b - prv.b, prv.a - a);
            if (p <= prv.p) pop_back();
            else {
                push_back({ a, b, p });
                break;
            }
        }
    }
    ll query(ll x) { // return minimum value at x
        Line tmp = { 0, 0, x };
        auto l = *prev(upper_bound(begin(), end(), tmp));
        return l.a * x + l.b;
    }
};

//-------------------------

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

struct Line {
    mutable ll a, b, p; // y = ax + b, x = p
    bool operator<(const Line& l) const { return a < l.a; }
    bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
    const ll inf = 9e18;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return 0; }
        if (x->a == y->a) x->p = (x->b > y->b ? inf : -inf);
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void add(ll a, ll b) {
        auto z = insert({ a, b, 0 }), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    ll query(ll x) {
        auto l = *lower_bound(x);
        return l.a * x + l.b;
    }
};
