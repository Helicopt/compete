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

char s[20][30];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, k;

    scanf("%d%d", &n, &k);

    int ans = 0;
    vector<map<char, int>> rec(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", s[i]);
        int l = strlen(s[i]);
        for (int j = 0; j < l; ++j)
        {
            rec[i][s[i][j]] += 1;
        }
    }
    for (int i = 1; i < (1 << n); ++i)
    {
        int tmp = 0;
        for (char c = 'a'; c <= 'z'; ++c)
        {
            int t = 0;
            for (int j = 0; j < n; ++j)
            {
                if ((i & (1 << j)) && rec[j][c])
                {
                    t += 1;
                }
            }
            if (t == k)
                tmp += 1;
        }
        ans = max(ans, tmp);
    }
    printf("%d\n", ans); // print the answer
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
