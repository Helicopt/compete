from collections import deque
import math

MAXN = 100007
MODP = 1000000007
INF = 0x3f3f3f3f
LINF = 0x3f3f3f3f3f3f3f3f
EPS = 1e-9

'''
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


'''


def read(s=' '):
    return input().strip().split(s)


def read_ints():
    return list(map(int, read()))


def solve(Ti):
    # print('Case #{}:'.format(Ti), end='')  # output case number
    n, = read_ints()
    a = read_ints()

    # TODO: do something

    ans = sum(a)
    print(ans)


if __name__ == '__main__':
    T = 1
    T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
