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
    l1, r1, l2, r2, = read_ints()
    if l2 <= r1 <= r2 or l1 <= r2 <= r1:
        print(max(l1, l2))
    else:
        print(l1 + l2)


if __name__ == '__main__':
    T = 1
    T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
