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

// int a[MAXN];

char s[107][91];

bool chk(const vector<VI> &x)
{
    set<int> s;
    for (int i = 0; i < x.size(); ++i)
    {
        bool found = false;
        // cerr << i << ": " << x[i].size() << endl;
        for (auto k : x[i])
        {
            // cerr << " " << k << endl;
            if (s.find(k) == s.end())
            {
                found = true;
                s.insert(k);
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%s", s[i]);
    }
    int l = 0, r = n * 10 + 1;
    vector<VI> a[10];
    for (int i = 0; i < 10; ++i)
        a[i].resize(n);
    int ans = -1;
    bool found = false;
    for (int i = l; i < r; ++i)
    {
        ans = i;
        for (int j = 0; j < n; ++j)
        {
            a[s[j][i % 10] - '0'][j].pb(i);
        }
        for (int j = 0; j < 10; ++j)
        {
            // cerr << "chk " << j << endl;
            if (chk(a[j]))
            {
                found = true;
                break;
            }
        }
        if (found)
            break;
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
