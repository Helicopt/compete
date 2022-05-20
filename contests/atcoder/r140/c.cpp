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

// int a[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, m;

    scanf("%d%d", &n, &m);
    VI ans;
    if ((n & 1) && m != n / 2 + 1 || (n & 1) == 0 && m != n / 2 && m != n / 2 + 1)
    {
        VI a;
        for (int i = 1; i <= n; ++i)
            if (i != m)
            {
                a.pb(i);
            }
        int pos = (a.size() >> 1);
        int turn = -1;
        ans.pb(m);
        int k = 1;
        while (pos >= 0 && pos < a.size())
        {
            ans.pb(a[pos]);
            pos += turn * k;
            turn = -turn;
            k++;
        }
    }
    else
    {
        VI a;
        for (int i = 1; i <= n; ++i)
            a.pb(i);
        int pos = (n >> 1);
        int turn = -1;
        if (m == pos)
        {
            pos = pos - 1;
            turn = 1;
        }
        int k = 1;
        while (pos >= 0 && pos < a.size())
        {
            ans.pb(a[pos]);
            pos += turn * k;
            turn = -turn;
            k++;
        }
    }

    printf("%d", ans[0]);
    for (int i = 1; i < ans.size(); ++i)
    {
        printf(" %d", ans[i]);
    }
    puts("");
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
