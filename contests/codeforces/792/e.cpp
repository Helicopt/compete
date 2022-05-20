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

    int n, k;

    scanf("%d%d", &n, &k);
    read_array<int>(a, n);
    sort(a, a + n);
    map<int, int> rec;
    for (int i = 0; i < n; ++i)
    {
        rec[a[i]] += 1;
    }
    priority_queue<PA> pq;
    for (auto &p : rec)
    {
        pq.push(PA(-p.SND, -p.FST));
    }
    int d = 0;
    set<int> used;
    while (1)
    {
        while (rec.find(d) != rec.end())
        {
            if (used.find(d) != used.end())
            {
                ++k;
                break;
            }
            else
            {
                used.insert(d);
                d++;
            }
        }
        while (!pq.empty() && -pq.top().SND < d)
            pq.pop();
        if (k == 0 || pq.empty())
            break;
        auto p = pq.top();
        // cerr << pq.size() << " " << d << " " << -p.FST << " " << -p.SND << endl;
        pq.pop();
        if (-p.FST - 1 > 0)
        {
            pq.push(PA(p.FST + 1, p.SND));
        }
        else
            used.insert(-p.SND);
        ++d;
        --k;
        // cerr << "--" << pq.size() << endl;
    }
    int ans = 0;
    while (!pq.empty())
    {
        auto p = pq.top();
        pq.pop();
        if (-p.SND >= d)
            ans++;
    }
    cout << ans << endl;
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
