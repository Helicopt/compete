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

int a[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int a, b, c;

    scanf("%d%d%d", &a, &b, &c);
    LL y = b;
    LL x = a + (c + b - 1) / b * b;
    LL z = c + x;
    cout << x << " " << y << " " << z << endl;
    // cerr << x % y - a << endl;
    // cerr << y % z - b << endl;
    // cerr << z % x - c << endl;
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
