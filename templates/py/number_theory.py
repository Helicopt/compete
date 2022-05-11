def gcd(x, y):
    while y:
        x, y = y, x % y
    return x


def lcm(x, y):
    return x * y // gcd(x, y)


def qpow(x, y, mod):
    res = 1
    while y:
        if y & 1:
            res = res * x % mod
        y >>= 1
        x = x * x % mod
    return res


def inv(x, mod):
    return qpow(x, mod - 2, mod)
