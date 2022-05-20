#include <bits/stdc++.h>
#define MAXN 3007
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

int a[MAXN], zeros[MAXN];
LL b[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, k;
    LL m;

    scanf("%d%d", &n, &k);
    read_array(a, n);
    zeros[0] = a[0] == 0;
    m = a[0];
    b[0] = a[0];
    for (int i = 1; i < n; ++i)
    {
        zeros[i] = zeros[i - 1] + (a[i] == 0);
        b[i] = b[i - 1] + a[i];
        m += a[i];
    }
    LL ans = 0;
    if ((LL)zeros[n - 1] * k + m < 0 || m > (LL)zeros[n - 1] * k)
    {
        puts("-1");
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                LL pre = zeros[min(i, j)];
                LL cur = zeros[max(i, j)] - zeros[min(i, j)];
                LL suf = zeros[n - 1] - zeros[max(i, j)];
                // - (pre + suf) * k <= m + d
                // (pre + suf) * k >= m + d
                if (i <= j)
                {
                    LL mx = b[i];
                    LL d = max(-(pre + suf) * k - m, cur * -k);
                    d = min(d, (pre + suf) * k - m);
                    LL mi = d + b[j];
                    if (mx >= mi)
                        ans = max(mx + 1 - mi, ans);
                }
                else
                {
                    LL d = max(-(pre + suf) * k - m, cur * k);
                    d = min(d, (pre + suf) * k - m);
                    LL mx = d + b[i];
                    LL mi = b[j];
                    if (mx >= mi)
                        ans = max(mx + 1 - mi, ans);
                }
            }
        }
        cout << ans << endl;
    }
}

int main()
{
    int T = 1;
    // scanf("%d", &T); // number of test cases
    for (int Ti = 1; Ti <= T; Ti++)
    {
        solve(Ti);
    }
    return 0;
}
