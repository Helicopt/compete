from collections import deque
import math

MAXN = 100007
MODP = 1000000007
INF = 0x3f3f3f3f
LINF = 0x3f3f3f3f3f3f3f3f
EPS = 1e-9

'''
{{libs}}
'''


def read(s=' '):
    return input().strip().split(s)


def read_ints():
    return list(map(int, read()))


def calc(v, d, r, x):
    u = x % (d + r)
    return x // (d + r) * (d * v) + (u * v if u <= d else d * v)


def solve(Ti):
    # print('Case #{}:'.format(Ti), end='')  # output case number
    d1, v1, r1, d2, v2, r2, x = read_ints()
    g1 = calc(v1, d1, r1, x)
    g2 = calc(v2, d2, r2, x)
    print('Takahashi' if g1 > g2 else ('Aoki' if g1 < g2 else 'Draw'))


if __name__ == '__main__':
    T = 1
    # T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
