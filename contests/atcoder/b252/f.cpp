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

LL a[MAXN];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n;
    LL L;

    cin >> n >> L;
    read_array<LL>(a, n);
    LL sum = 0;
    for (int i = 0; i < n; ++i)
        sum += (LL)a[i];
    if (L - sum > 0)
    {
        a[n] = L - sum;
        n += 1;
    }
    priority_queue<LL> pq;
    for (int i = 0; i < n; ++i)
    {
        pq.push(-a[i]);
    }
    LL ans = 0;
    while (pq.size() > 1)
    {
        LL x = -pq.top();
        pq.pop();
        LL y = -pq.top();
        // cerr << "merge " << x << ", " << y << " to " << x + y << endl;
        pq.pop();
        ans += x + y;
        pq.push(-x - y);
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
