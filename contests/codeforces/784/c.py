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
    a = read_ints()

    rec = {0: 0, 1: 0}

    for i in range(1, n+1):
        if a[i - 1] & 1:
            rec[i & 1] = rec.get(i & 1, 0) + 1
    if (rec[0] == n // 2 or rec[0] == 0) and (rec[1] == (n + 1) // 2 or rec[1] == 0):
        print('YES')
    else:
        print('NO')


if __name__ == '__main__':
    T = 1
    T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
