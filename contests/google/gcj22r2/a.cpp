#include <bits/stdc++.h>
#define MAXN 100007
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

int a[MAXN];

set<int> f[5009][4];

void solve(int Ti)
{
    printf("Case #%d: ", Ti); // print the case number

    int n, k;

    scanf("%d%d", &n, &k);
    if (k < n - 1 || (k & 1))
    {
        printf("IMPOSSIBLE\n");
    }
    else
    {
        int d = n;
        int offset = 1;
        int pos = 0;
        vector<PA> ans;
        while (d > 1)
        {
            // cerr << d << " " << k << " " << offset << " " << pos << endl;
            if (k - (d - 1) * (4 - pos) >= d - 3)
            {
                k -= (d - 1) * (4 - pos);
                offset += (d - 1) * 4;
                d -= 2;
                pos = 0;
            }
            else
            {
                int r = (k - (d - 3) - 2) / (d - 1);
                int npos = pos + r;
                int nof = offset + (d - 1) * 4;
                ans.pb(PA(offset + 1 + npos * (d - 1), nof + npos * (d - 3)));
                k -= (npos - pos) * (d - 1) + 2;
                d -= 2;
                offset = nof;
                pos = npos;
            }
        }
        printf("%d\n", (int)ans.size());
        for (auto &p : ans)
        {
            printf("%d %d\n", p.FST, p.SND);
        }
    }
    // for (int i = 0; i < 4; ++i)
    // {
    //     f[1][i].clear();
    //     f[1][i].insert(0);
    // }
    // for (int i = 3; i <= n; i += 2)
    // {
    //     for (int j = 3; j >= 0; --j)
    //     {
    //         f[i][j].clear();
    //         if (j == 3)
    //         {
    //             for (auto &k : f[i - 2][0])
    //                 f[i][j].insert(k + i - 1);
    //         }
    //         else
    //         {
    //             for (auto &k : f[i][j + 1])
    //                 f[i][j].insert(k + i - 1);
    //         }
    //         for (auto &k : f[i - 2][j])
    //             f[i][j].insert(k + 2);
    //     }
    // }
    // for (auto &k : f[n][0])
    // {
    //     cerr << k << endl;
    // }
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
