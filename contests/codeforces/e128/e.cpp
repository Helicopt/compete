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

char s1[MAXN], s2[MAXN];
int f[MAXN][2];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n;

    scanf("%d", &n);
    scanf("%s", s1);
    scanf("%s", s2);
    int start = 0;
    int end = n - 1;
    while (start < n && s1[start] == '.' && s2[start] == '.')
        ++start;
    while (end >= 0 && s1[end] == '.' && s2[end] == '.')
        --end;
    if (start <= end)
    {
        int i = start;
        if (s1[i] == '*' && s2[i] == '*')
        {
            f[1][0] = 1;
            f[1][1] = 1;
        }
        if (s1[i] == '*' && s2[i] == '.')
        {
            f[1][0] = 0;
            f[1][1] = 1;
        }
        if (s1[i] == '.' && s2[i] == '*')
        {
            f[1][0] = 1;
            f[1][1] = 0;
        }
        if (s1[i] == '.' && s2[i] == '.')
        {
            f[1][0] = 0;
            f[1][1] = 0;
        }
        for (int i = start + 1; i <= end; ++i)
        {
            if (s1[i] == '*' && s2[i] == '*')
            {
                f[i - start + 1][0] = min(f[i - start][0] + 2, f[i - start][1] + 2);
                f[i - start + 1][1] = min(f[i - start][0] + 2, f[i - start][1] + 2);
            }
            if (s1[i] == '*' && s2[i] == '.')
            {
                f[i - start + 1][0] = min(f[i - start][0] + 1, f[i - start][1] + 2);
                f[i - start + 1][1] = min(f[i - start][0] + 2, f[i - start][1] + 2);
            }
            if (s1[i] == '.' && s2[i] == '*')
            {
                f[i - start + 1][0] = min(f[i - start][0] + 2, f[i - start][1] + 2);
                f[i - start + 1][1] = min(f[i - start][0] + 2, f[i - start][1] + 1);
            }
            if (s1[i] == '.' && s2[i] == '.')
            {
                f[i - start + 1][0] = min(f[i - start][0] + 1, f[i - start][1] + 2);
                f[i - start + 1][1] = min(f[i - start][0] + 2, f[i - start][1] + 1);
            }
            // cerr << f[i - start + 1][0] << " " << f[i - start + 1][1] << endl;
        }
        int ans = min(f[end - start + 1][0], f[end - start + 1][1]);
        printf("%d\n", ans); // print the answer
    }
    else
    {
        puts("0");
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