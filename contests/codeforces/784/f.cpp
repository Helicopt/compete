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

int a[MAXN], pre[MAXN], suf[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n;

    scanf("%d", &n);
    read_array<int>(a, n);
    pre[0] = a[0];
    for (int i = 1; i < n; ++i)
        pre[i] = pre[i - 1] + a[i];
    suf[n] = 0;
    for (int i = n - 1; i >= 0; --i)
        suf[i] = suf[i + 1] + a[i];
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int l = i;
        int r = n;
        while (l + 1 < r)
        {
            int m = (l + r) >> 1;
            if (suf[m] > pre[i])
                l = m;
            else
                r = m;
        }
        if (suf[r] == pre[i])
            ans = max(ans, i + 1 + n - r);
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
