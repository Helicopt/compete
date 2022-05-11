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


class Solution:
    def entry(n, a):
        # TODO: do something
        return sum(a)


def solve(Ti):
    n, = read_ints()
    a = read_ints()

    sol = Solution()

    ans = sol.entry(n, a)

    print(ans)


if __name__ == '__main__':
    T = 1
    # T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
