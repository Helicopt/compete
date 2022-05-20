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

char s[MAXN];

int check(char *s, int n, int k, int x)
{
    for (int i = 0; i < x; ++i)
    {
        map<char, int> rec;
        for (int j = 0; j < n / x; ++j)
        {
            rec[s[i + j * x]]++;
        }
        int cnt = 0;
        for (auto &p : rec)
        {
            if (p.SND > cnt)
                cnt = p.SND;
        }
        if (n / x - cnt > k)
            return 0;
        k -= n / x - cnt;
    }
    return 1;
}

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, k;

    scanf("%d%d", &n, &k);

    scanf("%s", s);
    int ans = n;
    for (int i = 1; i < n; ++i)
    {
        if (n % i != 0)
            continue;
        if (check(s, n, k, i))
        {
            ans = i;
            break;
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
