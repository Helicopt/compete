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

int t[MAXN], y[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, k;

    scanf("%d%d", &n, &k);
    t[0] = 1;
    y[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &t[i], &y[i]);
    }
    LL ans = -LINF, tot = 0, mi = 0;
    int cnt = 0;
    priority_queue<int> pq;
    for (int i = n; i >= 0; --i)
    {
        while (pq.size() > max(k - cnt, 0))
        {
            if (pq.top() < 0)
                mi -= pq.top();
            pq.pop();
        }
        if (t[i] == 1)
        {
            if (k >= cnt)
            {
                ans = max(ans, tot - mi + y[i]);
            }
            cnt += 1;
        }
        else
        {
            if (pq.size() + 1 <= k - cnt)
            {
                if (y[i] < 0)
                    mi += y[i];
                pq.push(y[i]);
            }
            else
            {
                if (!pq.empty() && pq.top() > y[i])
                {
                    if (pq.top() < 0)
                        mi -= pq.top();
                    if (y[i] < 0)
                        mi += y[i];
                    pq.pop();
                    pq.push(y[i]);
                }
            }
            tot += y[i];
        }
        // cerr << ans << " " << tot << " " << mi << endl;
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
