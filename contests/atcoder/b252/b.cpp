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

int a[MAXN], b[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, k;

    scanf("%d%d", &n, &k);
    read_array(a + 1, n);
    read_array(b + 1, k);
    int mini = -1;
    for (int i = 1; i <= n; ++i)
    {
        mini = max(mini, a[i]);
    }
    bool flag = false;
    for (int i = 1; i <= k; ++i)
    {
        if (a[b[i]] == mini)
        {
            flag = true;
        }
    }
    puts(flag ? "Yes" : "No");
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
