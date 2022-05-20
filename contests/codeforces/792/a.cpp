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

char s[100];

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number
    scanf("%s", s);
    int n = strlen(s);
    if (n == 1)
    {
        printf("%c\n", s[0]);
        return;
    }
    if (n == 2)
    {
        printf("%c\n", s[1]);
    }
    if (n > 2)
    {
        char k = 'z';
        for (int i = 0; i < n; ++i)
        {
            if (s[i] < k)
            {
                k = s[i];
            }
        }
        printf("%c\n", k);
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
