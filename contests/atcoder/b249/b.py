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
    s = input().strip()
    has_upper = False
    has_lower = False
    has_twin = False
    rec = {}
    for c in s:
        if ord('A') <= ord(c) <= ord('Z'):
            has_upper = True
        if ord('a') <= ord(c) <= ord('z'):
            has_lower = True
        rec[c] = rec.get(c, 0) + 1
        if rec[c] > 1:
            has_twin = True
    if has_upper and has_lower and not has_twin:
        print('Yes')
    else:
        print('No')


if __name__ == '__main__':
    T = 1
    # T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
