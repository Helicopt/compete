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
    print('Case #{}:'.format(Ti), end='')  # output case number
    n, k = read_ints()
    if k < n - 1 or k >= n * n:
        print(' IMPOSSIBLE')
    else:
        d = n
        ans.append()
        while d > 1 and k - (d - 1) * 4 >= d - 3:
            d -= 2

        

if __name__ == '__main__':
    T = 1
    T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
