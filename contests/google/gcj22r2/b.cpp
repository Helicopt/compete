#include <bits/stdc++.h>
#define MAXN 2007
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

char a[MAXN][MAXN], b[MAXN][MAXN];

void solve(int Ti)
{
    printf("Case #%d: ", Ti); // print the case number

    int n;

    scanf("%d", &n);
    int ox = (MAXN >> 1), oy = (MAXN >> 1);
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    cerr << n << endl;
    if (n > 300)
    {
        cout << "0" << endl;
    }
    else
    {
        for (int x = -n; x <= n; ++x)
        {
            for (int y = -n; y <= n; ++y)
            {
                if (round(sqrt(x * x + y * y)) <= n)
                {
                    // cerr << ox + x << " " << oy + y << endl;
                    a[ox + x][oy + y] = 1;
                }
            }
        }
        for (int i = 0; i <= n; ++i)
        {
            for (int x = -i; x <= i; ++x)
            {
                int y = round(sqrt(i * i - x * x));
                b[ox + x][oy + y] = 1;
                b[ox + x][oy - y] = 1;
                b[ox + y][oy + x] = 1;
                b[ox - y][oy + x] = 1;
                // cerr << ox + x << " " << oy + y << endl;
                // cerr << ox + x << " " << oy - y << endl;
                // cerr << ox + y << " " << oy + x << endl;
                // cerr << ox - y << " " << oy + x << endl;
            }
        }
        int ans = 0;
        for (int i = -n; i <= n; ++i)
        {
            for (int j = -n; j <= n; ++j)
            {
                if (a[ox + i][oy + j] != b[ox + i][oy + j])
                    ans += 1;
            }
        }
        cout << ans << endl;
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
