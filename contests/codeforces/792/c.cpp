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

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, m;

    scanf("%d%d", &n, &m);
    vector<vector<int>> g(n);
    vector<vector<PA>> dec(n);
    vector<vector<int>> dec_i(n), dec_l(n), dec_r(n);
    bool flag = true;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int x;
            scanf("%d", &x);
            g[i].pb(x);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        vector<int> tmp = g[i];
        sort(tmp.begin(), tmp.end());
        for (int j = 0; j < m; ++j)
        {
            int l = lower_bound(tmp.begin(), tmp.end(), g[i][j]) - tmp.begin();
            int r = upper_bound(tmp.begin(), tmp.end(), g[i][j]) - tmp.begin();
            dec[i].pb(PA(l, r));
            if (j < l || j >= r)
            {
                dec_i[i].pb(j);
                dec_l[i].pb(l);
                dec_r[i].pb(r);
            }
        }
        if (dec_i[i].size() > 2)
        {
            flag = false;
        }
        // cerr << i << ": " << dec[i].size() << endl;
        // for (int j = 0; j < dec[i].size(); j++)
        // {
        //     cerr << dec[i][j].FST << " " << dec[i][j].SND << "; " << endl;
        // }
    }
    int ansi = 0, ansj = 0;
    int exec = false;
    if (flag)
    {
        for (int i = 0; i < n; ++i)
        {
            if (dec_i[i].size() > 0)
            {
                ansi = dec_i[i][0];
                ansj = dec_i[i][1];
                exec = true;
            }
        }
        // cerr << " !" << exec << endl;
        if (exec)
            for (int i = 0; i < n; ++i)
            {
                if (!(dec[i][ansj].FST <= ansi && ansi < dec[i][ansj].SND &&
                      dec[i][ansi].FST <= ansj && ansj < dec[i][ansi].SND))
                {
                    flag = false;
                }
            }
    }

    if (!flag)
    {
        puts("-1");
    }
    else
    {
        printf("%d %d\n", ansi + 1, ansj + 1);
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
