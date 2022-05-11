import re
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
    def isMatch(self, s: str, p: str) -> bool:
        pp = []
        prev = '.'
        for c in p:
            if c == '*':
                if prev == '.':
                    pp[-1] = '[a-z]*'
                else:
                    pp[-1] = '[%s]*' % prev
            elif c == '.':
                pp.append('[a-z]')
            else:
                pp.append(c)
            prev = c
        pp = ''.join(pp)
        # print(pp, s)
        m = re.match(pp, s)
        if m is None:
            return False
        return m.end() == len(s)


def solve(Ti):
    sol = Solution()

    ans = sol.isMatch('aab', 'c*a*b')

    print(ans)


if __name__ == '__main__':
    T = 1
    # T = int(input())  # read number of test cases
    for Ti in range(T):
        solve(Ti + 1)
