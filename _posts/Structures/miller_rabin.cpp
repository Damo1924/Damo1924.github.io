#include <iostream>
using namespace std;
typedef unsigned long long ll;

ll pow(ll x, ll y, ll m) { // x ^ y % m
    if (y == 1) return x % m;
    ll t = pow(x, y / 2, m);
    t = t * t % m;
    if (y % 2) return t * x % m;
    return t;
}

bool isComposite(ll n, ll a, ll d, ll s) {
    ll x = pow(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = x * x % n;
        if (x == n - 1) return false;
    }
    return true;
}

bool isPrime(ll n) { // Miller-Rabin
    if (n == 1) return false;
    ll d = n - 1, s = 0;
    while (d % 2 == 0) s++, d /= 2;
    for (int a : { 2, 7, 61 }) { // always correct for all unsigned int
        if (n == a) return true;
        if (isComposite(n, a, d, s)) return false;
    }
    return true;
}
