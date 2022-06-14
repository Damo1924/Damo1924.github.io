#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;
typedef unsigned long long ll;

ll modpow(ll x, ll y, ll mod) {
    ll ret = 1;
    while (y) {
        if (y % 2) ret = (__int128) ret * x % mod;
        x = (__int128) x * x % mod;
        y /= 2;
    }
    return ret;
}

bool miller_rabin(ll n, ll a, ll d, ll s) {
    ll x = modpow(a, d, n);
    if (x == 1) return 0;
    for (int r = 0; r < s; r++) {
        if (x == n - 1) return 0;
        x = (__int128) x * x % n;
    }
    return 1;
}

bool isPrime(ll n) {
    if (n == 1) return 0;
    ll d = n - 1, s = 0;
    while (d % 2 == 0) s++, d /= 2;
    for (ll a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
        if (n % a == 0) return n == a;
        if (miller_rabin(n, a, d, s)) return 0;
    }
    return 1;
}

ll gcd(ll x, ll y) {
    while (y) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}

ll pollard_rho(ll n) {
    ll x = 2, y = 2, g = 1, c = 1;
    auto f = [&](ll x) { return ((__int128) x * x % n + c) % n; };
    while (g == 1) {
        x = f(x), y = f(f(y));
        g = gcd(x > y ? x - y : y - x, n);
        if (g == n) {
            x = y = rand() % (n - 2);
            c = rand() % 10 + 1;
            g = 1;
        }
    }
    return g;
}

vector<ll> factors;
void factorize(ll n) {
    if (isPrime(n)) factors.push_back(n);
    else {
        ll g = (n % 2 ? pollard_rho(n) : 2);
        factorize(g);
        factorize(n / g);
    }
}
