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

int f[MAXN][MAXN], f1[MAXN], f2[MAXN], f3[MAXN], f4[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, p;
    scanf("%d%d", &n, &p);
    f[0][0] = 1;
    f1[0] = 1;
    auto dd = [](int x) -> int
    {
        return (x == 0) ? 26 : 25;
    };
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            f[i][j] = 0;
            if (j - 2 >= 0)
                f[i][j] = (f[i][j] + (LL)f1[j - 2] * dd(j - 2)) % p;
            if (j - 3 >= 0)
                f[i][j] = (f[i][j] + (LL)f2[j - 3] * dd(j - 3)) % p;
            if (j - 4 >= 0)
                f[i][j] = (f[i][j] + (LL)f3[j - 4] * dd(j - 4)) % p;
            if (j - 5 >= 0)
                f[i][j] = (f[i][j] + (LL)f4[j - 5] * dd(j - 5)) % p;
        }
        for (int j = 0; j < n; ++j)
        {
            f1[j] = (f1[j] + f[i][j]) % p;
            if (i - 9 >= 0)
                f1[j] = (f1[j] + p - f[i - 9][j]) % p;
            if (i - 9 >= 0)
                f2[j] = (f2[j] + f[i - 9][j]) % p;
            if (i - 99 >= 0)
                f2[j] = (f2[j] + p - f[i - 99][j]) % p;
            if (i - 99 >= 0)
                f3[j] = (f3[j] + f[i - 99][j]) % p;
            if (i - 999 >= 0)
                f3[j] = (f3[j] + p - f[i - 999][j]) % p;
            if (i - 999 >= 0)
                f4[j] = (f4[j] + f[i - 999][j]) % p;
        }
    }
    // for (int i = 0; i < 12; ++i)
    // {
    //     for (int j = 0; j < 12; ++j)
    //     {
    //         printf("%d ", f[i][j]);
    //     }
    //     printf("\n");
    // }
    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans = (ans + f[n][i]) % p;
    cout << ans << endl;
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
