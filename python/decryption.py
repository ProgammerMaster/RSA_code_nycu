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


if __name__ == '__main__':
    map_dic = {}
    n, e, msg = input().split()
    n = int(n)
    e = int(e)

    msg = list(map(int, msg.split(',')))

    for i in range(0, 128):
        map_dic[modpow(i, e, n)] = i

    for i in msg:
        print(chr(map_dic[i]), end='')
        # if i in map_dic:
        #   print(chr(map_dic[i]), end='')
        # else:
        #tmp = modpow(i, d, n)
        #    map_dic[i] = tmp
       #     print(chr(tmp), end='')
