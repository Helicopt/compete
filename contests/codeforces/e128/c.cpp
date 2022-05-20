#include <bits/stdc++.h>
#define MAXN 200007
#define MODP 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define PI 3.14159265358979323846
#define EPS 1e-9
#define FST first
#define SND second
#define BE begin()
#define ED end()
#define pb push_back

using namespace std;

typedef long long LL;
typedef pair<int, int> PA;
typedef pair<LL, LL> PL;
typedef std::vector<int> VI;
typedef std::vector<long long> VL;

/*
{{libs}}
*/

template <typename T>
inline void read_array(T *a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        a[i] = (T)x;
    }
}

char s[MAXN];
int r0[MAXN], r1[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n;

    scanf("%s", s);
    n = strlen(s);
    r0[n] = r1[n] = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        r0[i] = r0[i + 1] + (s[i] == '0');
        r1[i] = r1[i + 1] + (s[i] == '1');
    }
    int ans = n << 1;
    int s0 = r0[0];
    int l1 = 0;
    int l0 = 0;
    for (int i = 0; i <= n; ++i)
    {
        int l = i - 1, r = n + 1;
        while (l + 1 < r)
        {
            int m = (l + r) >> 1;
            // cerr << m << " " << s0 - l0 - r0[m] << " " << l1 + r1[m] << " " << s0 << " " << l0 << " " << l1 << " " << r0[m] << endl;
            if (s0 - l0 - r0[m] >= l1 + r1[m])
            {
                r = m;
            }
            else
            {
                l = m;
            }
        }
        // cerr << i << ": " << r << endl;
        if (r <= n)
            ans = min(ans, max(s0 - l0 - r0[r], l1 + r1[r]));
        else
            ans = min(ans, max(s0 - l0, l1));

        l1 += (s[i] == '1');
        l0 += (s[i] == '0');
    }
    printf("%d\n", ans); // print the answer
}

int main()
{
    int T = 1;
    scanf("%d", &T); // number of test cases
    for (int Ti = 1; Ti <= T; Ti++)
    {
        solve(Ti);
    }
    return 0;
}
