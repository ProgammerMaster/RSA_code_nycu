def modpow(base: int, exp: int, modulus: int) -> int:
    # print(modpow.inspect_types())
    result: int = 1
    base %= modulus
    while exp > 0:
        if (exp & 1):
            result = (result * base) % modulus
        base = (base ** 2) % modulus
        exp >>= 1

    return result


if __name__ == '__main__':
    map_dic = {}
    n, e, msg = input().split()

    msg = list(msg)

    ans = []
    n = int(n)
    e = int(e)
    for i in msg:
        if i in map_dic:
            ans.append(map_dic[i])
        else:
            tmp = modpow(ord(i), e, n)
            map_dic[i] = tmp
            ans.append(tmp)
    print(*ans, sep=',')
