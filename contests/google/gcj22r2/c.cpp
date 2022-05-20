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

LL dist(PA x, PA y)
{
    return ((LL)(x.FST - y.FST)) * (x.FST - y.FST) + ((LL)(x.SND - y.SND)) * (x.SND - y.SND);
}

int chk(const vector<PA> &ans, const VI &v)
{
    if (v[0] == 0)
    {
        puts("POSSIBLE");
        for (int i = 0; i < ans.size(); ++i)
            printf("%d %d\n", ans[i].FST, ans[i].SND);
        return 1;
    }
    else
        return 0;
}

int dfs(int dep, int n, const vector<PA> &childs, const vector<PA> &cans, VI &a, vector<PA> &ans, VI &v)
{
    if (dep == n)
    {
        if (chk(ans, v))
        {
            return true;
        }
        return false;
    }
    for (int i = dep; i < n; ++i)
    {
        swap(a[dep], a[i]);
        LL dis = LINF;
        LL mdis = 0;
        int choose = -1;
        for (int j = 0; j < cans.size(); ++j)
        {
            if (v[j] == 1)
                continue;
            LL ed = dist(childs[a[dep]], cans[j]);
            LL ed2 = dist(cans[j], cans[0]);
            if (ed < dis || ed == dis && ed2 > mdis || ed == dis && ed2 == mdis && j > choose)
            {
                dis = ed;
                mdis = ed2;
                choose = j;
            }
        }
        v[choose] = 1;
        ans[dep] = PA(a[dep] + 1, choose + 1);
        if (dfs(dep + 1, n, childs, cans, a, ans, v))
        {
            return true;
        }
        swap(a[dep], a[i]);
        v[choose] = 0;
    }
    return false;
}

void solve(int Ti)
{
    printf("Case #%d: ", Ti); // print the case number

    int n;

    scanf("%d", &n);
    vector<PA> childs(0);
    vector<PA> cans(0);
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        childs.pb(PA(x, y));
    }
    for (int i = 0; i <= n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        cans.pb(PA(x, y));
    }
    VI a(n);
    for (int i = 0; i < n; ++i)
        a[i] = i;
    vector<PA> ans(n, PA(0, 0));
    VI v(n + 1, 0);
    int flag = dfs(0, n, childs, cans, a, ans, v);
    if (!flag)
    {
        puts("IMPOSSIBLE");
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
