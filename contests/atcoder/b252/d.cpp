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

int a[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n;

    scanf("%d", &n);
    read_array<int>(a, n);
    map<int, int> m;
    for (int i = 0; i < n; ++i)
    {
        m[a[i]]++;
    }
    LL ans = (LL)n * (n - 1) * (n - 2) / 6;
    for (auto k : m)
    {
        if (k.SND > 1)
            ans -= (LL)k.SND * (k.SND - 1) / 2 * (n - k.SND);
        if (k.SND > 2)
            ans -= (LL)k.SND * (k.SND - 1) * (k.SND - 2) / 6;
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
