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
    s = input().split('W')
    f = True
    for k in s:
        if k == '':
            continue
        flag = False
        for i in range(1, len(k)):
            if k[i] != k[0]:
                flag = True
                break
        f = f and flag
        if not f:
            break
    print('YES' if f else 'NO')


if __name__ == '__main__':
    T = 1
    T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
