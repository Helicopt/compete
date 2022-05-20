#include <bits/stdc++.h>
#define MAXN 600007
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

typedef struct node
{
    bool cov;
    int cnt;
} Node;

Node tr_x[MAXN], tr_y[MAXN];

void insert(Node *tr, int d, int l, int r, int x, int c)
{
    if (l == r)
    {
        tr[d].cnt += c;
        if (tr[d].cnt == 0)
            tr[d].cov = false;
        else
            tr[d].cov = true;
        return;
    }
    int m = (l + r) >> 1;
    int ll = d << 1, rr = ll + 1;
    if (x <= m)
        insert(tr, ll, l, m, x, c);
    else
        insert(tr, rr, m + 1, r, x, c);
    tr[d].cnt = tr[ll].cnt + tr[rr].cnt;
    if (tr[ll].cov && tr[rr].cov)
        tr[d].cov = true;
    else
        tr[d].cov = false;
}

bool query(Node *tr, int d, int l, int r, int x, int y)
{
    if (l == x && y == r)
        return tr[d].cov;
    int m = (l + r) >> 1;
    int ll = d << 1, rr = ll + 1;
    if (y <= m)
        return query(tr, ll, l, m, x, y);
    else if (x > m)
        return query(tr, rr, m + 1, r, x, y);
    else
        return query(tr, ll, l, m, x, m) && query(tr, rr, m + 1, r, m + 1, y);
}

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, m;

    scanf("%d%d", &n, &m);
    while (m--)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            insert(tr_x, 1, 1, n, x, 1);
            insert(tr_y, 1, 1, n, y, 1);
        }
        if (op == 2)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            insert(tr_x, 1, 1, n, x, -1);
            insert(tr_y, 1, 1, n, y, -1);
        }
        if (op == 3)
        {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            bool coveredx = query(tr_x, 1, 1, n, x1, x2);
            bool coveredy = query(tr_y, 1, 1, n, y1, y2);
            if (coveredx || coveredy)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
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
