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

int a[MAXN], b[MAXN];

LL tr[MAXN];

void insert(int x, int n, int v)
{
    int o = v;
    v = v - b[x];
    b[x] = o;
    while (x <= n)
    {
        tr[x] = tr[x] + v;
        x += x & -x;
    }
}

LL query(int x, int n)
{
    LL ans = 0;
    while (x > 0)
    {
        ans += tr[x];
        x -= x & -x;
    }
    return ans;
}

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, m;

    scanf("%d%d", &n, &m);
    read_array<int>(a + 1, n);
    queue<PA> q;
    int base = 0;
    for (int i = 1; i <= n; ++i)
    {
        tr[i] = 0;
        b[i] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        q.push(PA(i, a[i]));
        insert(i, n, a[i]);
    }
    // cerr << query(n, n) << endl;
    while (m--)
    {
        int op, x, y;
        scanf("%d%d", &op, &x);
        if (op == 2)
        {
            base = x;
            while (!q.empty())
            {
                // cerr << "! " << q.front().FST << endl;
                insert(q.front().FST, n, 0);
                q.pop();
            }
            // for (int i = 1; i <= n; ++i)
            // {
            //     cerr << tr[i] << " " << b[i] << endl;
            // }
        }
        else
        {
            scanf("%d", &y);
            q.push(PA(x, y));
            insert(x, n, y - base);
        }
        LL ans = (LL)base * n + query(n, n);
        printf("%lld\n", ans);
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
