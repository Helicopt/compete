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
    n, m = read_ints()
    top_x, top_y = -1, -1
    min_col = m + 1
    for i in range(n):
        s = input()
        for j, c in enumerate(s):
            if c == 'R':
                if top_x < 0:
                    top_x = i
                    top_y = j
                min_col = min(min_col, j)
    if min_col == top_y:
        print('YES')
    else:
        print('NO')


if __name__ == '__main__':
    T = 1
    T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
