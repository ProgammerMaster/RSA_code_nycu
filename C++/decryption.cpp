// RSA_dicode.cpp 
#pragma GCC optimize(3,"Ofast", "inline")

#include <iostream>
#include <sstream>
#include <map>
using namespace std;
#define speed_up ios_base::sync_with_stdio(false), cin.tie(0)
#define ll long long 

inline void mulmod(ll a, ll b, ll m, ll& res) {

    res = 0;
    ll temp_b;

    /* Only needed if b may be >= m */
    if (b >= m) {
        (m > UINT64_MAX / 2u) ? b -= m : b %= m;
    }

    while (a != 0) {
        if (a & 1) {
            /* Add b to res, modulo m, without overflow */
            if (b >= m - res) { res -= m; }/* Equiv to if (res + b >= m), without overflow */

            res += b;
        }
        a >>= 1;

        /* Double b, modulo m */
        temp_b = b;
        if (b >= m - b) { temp_b -= m; }      /* Equiv to if (2 * b >= m), without overflow */
        b += temp_b;
    }
}

inline ll modpow(ll base, ll exp, ll modulus) {
    base %= modulus;
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) mulmod(result, base, modulus, result);//(result * base) % modulus;
        mulmod(base, base, modulus, base); //(base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

int main() {
    speed_up;
    ll n, e, val;
    string inp;
    char pa;
    cin >> n >> e >> inp;
    stringstream ss(inp);
    map <ll, char> rsa_map;
    for (int i = 0; i < 128; i++) {
        rsa_map[modpow(i, e, n)] = i;
    }

    while (!ss.eof()) {
        ss >> val >> pa;
        cout << rsa_map[val];
    }
    return 0;
}