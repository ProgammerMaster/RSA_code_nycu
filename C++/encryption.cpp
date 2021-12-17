// RSA_encode.cpp 
#pragma GCC optimize(3,"Ofast", "inline")
#include <iostream>
#include <string>
using namespace std;
#define speed_up ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define ull unsigned long long

//m^e mod n 

inline void mulmod(ull a, ull b, ull m, ull& res) {
    res = 0;
    ull temp_b;

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

inline void modpow(ull base, ull exp, ull modulus, ull& ans) {
    base %= modulus;
    ans = 1;
    while (exp > 0) {
        if (exp & 1) mulmod(ans, base, modulus, ans);//(result * base) % modulus;
        mulmod(base, base, modulus, base); //(base * base) % modulus;
        exp >>= 1;
    }
}

int main() {
    speed_up;
    ull n, e;
    string m;
    cin >> n >> e >> m;
    //map<char, ull> encode_map;
    ull map_arr[128] = { 0 };
    ull size = m.size(), change;
    for (auto& elme : m) {
        //auto find_map = encode_map.find(elme);
        if (map_arr[elme] == 0) {
            modpow(elme, e, n, change);
            map_arr[elme] = change;
            cout << change;
        }
        else {
            cout << map_arr[elme];
        }
        size--;
        (size == 0) ? cout << " " : cout << ",";
    }
    return 0;
}