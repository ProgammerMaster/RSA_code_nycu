from math import sqrt


def modpow(base: int, exp: int, modulus: int) -> int:
    result: int = 1
    base %= modulus
    exp = int(exp)
    while exp > 0:
        if (exp & 1):
            result = (result * base) % modulus
        base = (base**2) % modulus
        exp >>= 1

    return result


def private_key(n: int, e: int) -> int:
    p: int
    q: int
    if not(n % 2):
        p, q = 2, n / 2
    else:
        for i in range(3, int(sqrt(n) + 1), 2):
            if not(n % i):
                p, q = i, n/i
                break

    m = (p-1)*(q-1)
    g, x, y = egcd(e, m)
    return x % m


def egcd(a: int, b: int):
    if not(a):
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)


if __name__ == '__main__':
    map_dic = {}
    n, e, msg = input().split()
    n = int(n)
    e = int(e)

    msg = list(map(int, msg.split(',')))

    d = private_key(n, e)
    for i in msg:
        if i in map_dic:
            print(chr(map_dic[i]), end='')
        else:
            tmp = modpow(i, d, n)
            map_dic[i] = tmp
            print(chr(tmp), end='')
