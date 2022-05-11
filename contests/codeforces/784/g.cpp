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

char g[100][100];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, m;

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", g[i] + 1);
    }
    for (int i = 1; i <= m; ++i)
    {
        int cnt = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (g[j][i] == '*')
            {
                cnt += 1;
                g[j][i] = '.';
            }
            else if (g[j][i] == 'o')
            {
                for (int k = j - 1; k >= j - cnt; --k)
                {
                    g[k][i] = '*';
                }
                cnt = 0;
            }
        }
        if (cnt)
        {
            for (int k = n - cnt + 1; k <= n; ++k)
            {
                g[k][i] = '*';
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        puts(g[i] + 1);
    }
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
