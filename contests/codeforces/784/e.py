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


def solve(Ti):
    # print('Case #{}:'.format(Ti), end='')  # output case number
    n, = read_ints()
    rec_a = {}
    rec_b = {}
    for i in range(n):
        s = input()
        if s[0] not in rec_a:
            rec_a[s[0]] = {}
        rec_a[s[0]][s[1]] = rec_a[s[0]].get(s[1], 0) + 1
        if s[1] not in rec_b:
            rec_b[s[1]] = {}
        rec_b[s[1]][s[0]] = rec_b[s[1]].get(s[0], 0) + 1
    ans = 0
    for k, v in rec_a.items():
        sa = 0
        for kk, vv in v.items():
            sa += vv
        for kk, vv in v.items():
            ans += vv * (sa - vv)
    for k, v in rec_b.items():
        sa = 0
        for kk, vv in v.items():
            sa += vv
        for kk, vv in v.items():
            ans += vv * (sa - vv)
    print(ans // 2)


if __name__ == '__main__':
    T = 1
    T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
