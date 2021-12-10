// RSA_dicode.cpp 

#include <iostream>
#include <sstream>
#include <map>
#include <tgmath.h>
#include <tuple>
using namespace std;
#define speed_up ios_base::sync_with_stdio(false), cin.tie(0)
#define ull unsigned long long 

inline void mulmod(ull a, ull b, ull m , ull& res) {
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

inline ull modpow(ull base, ull exp, ull modulus) {
    base %= modulus;
    ull result = 1;
    while (exp > 0) {
        if (exp & 1) mulmod(result, base, modulus , result);//(result * base) % modulus;
        mulmod(base, base, modulus , base); //(base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

int main() {
    speed_up;
    ull n, e , val; 
    string inp; 
    char pa; 
    cin >> n >> e >> inp;
    stringstream ss(inp);
    map<int, char> rsa_map;
    //

    ull p = 0, q = 0;
    if (!(n % 2)) { p = 2;  q = n / 2; }
    else {
        ull length = std::sqrt(n);
		for (ull i = 3; i < length; i += 2) {
            if (!(n % i)) { // n%i == 0 find p and q  
                p = i;
                q = n / i;
                break;
            }
        }
    }// get p and q 

    ull tol = (p - 1) * (q - 1), private_key = 1, t = 0 ;
    ull s1 = 0, t1 = 1, a1 = e, b1 = tol;//tol = (p - 1)*(q - 1); 

    while (b1) {
        ull tmp = floor(a1 / b1);
        tie(private_key, s1) = std::tuple<ull, ull>(s1, private_key - tmp * s1);
        tie(t, t1) = std::tuple<ull, ull>(t1, 0 - tmp * t1);
        tie(a1, b1) = std::tuple<ull, ull>(b1, a1 - tmp * b1);
    }
    
	if (static_cast<long long int>(private_key) < 0) {
        private_key = static_cast<long long int>(private_key) + tol;
    }
    
    while (!ss.eof()) {
        ss >> val >> pa; 
        auto Find = rsa_map.find(val); 
        if (Find == rsa_map.end()) {
            char change = static_cast<char>(modpow(val, private_key, n));
            rsa_map[val] = change; 
            cout << change; 

        }
        else {
            cout << Find->second; 
        }
    }


    return 0; 
}

