#include <bits/stdc++.h>
#define MAXN 3007
#define MODP 998244353
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
int v[MAXN], tot, pcnt;

void dfs(int x, int n)
{
    v[x] = 1;
    if (a[x] != -1)
        dfs(a[x], n);
}

void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        v[i] = 0;
    }
    tot = 0;
    pcnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (v[i] == 0)
        {
            dfs(i, n);
            tot += 1;
        }
        if (a[i] == -1)
            pcnt++;
    }
}

LL calc(int n, int k)
{
    LL ret = 0;
    if (k > tot)
        return 0;
    if (tot - pcnt > k)
        return 0;
    int r = k - (tot - pcnt);
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] == -1)
        {
            
        }
    }
    return ret;
}

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n;

    scanf("%d", &n);
    read_array<int>(a + 1, n);
    LL ans = 0;
    init(n);
    for (int i = 1; i <= n; ++i)
    {
        LL cnt = calc(n, i);
        ans += cnt * i % MODP;
        ans %= MODP;
    }
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
