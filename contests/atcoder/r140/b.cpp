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

char s[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n;

    scanf("%d", &n);
    scanf("%s", s + 1);
    s[0] = 0;
    s[n + 1] = 0;
    set<PA> q;
    for (int i = 1; i <= n - 2; ++i)
    {
        if (s[i] == 'A' && s[i + 1] == 'R' && s[i + 2] == 'C')
        {
            int cnt = 1;
            while (i - cnt >= 1 && i + 2 + cnt <= n && s[i - cnt] == 'A' && s[i + 2 + cnt] == 'C')
            {
                ++cnt;
            }
            q.insert(PA(cnt, i + 1));
        }
    }
    int ans = 0;
    while (!q.empty())
    {
        ++ans;
        if (ans & 1)
        {
            PA p = *q.rbegin();
            // cerr << "q " << p.FST << " " << p.SND << endl;
            q.erase(p);
            p.FST -= 1;
            if (p.FST > 0)
            {
                q.insert(p);
            }
        }
        else
        {
            PA p = *q.begin();
            q.erase(p);
            // cerr << "q " << p.FST << " " << p.SND << endl;
        }
    }
    printf("%d\n", ans);
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
