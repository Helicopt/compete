#include <bits/stdc++.h>
#define MAXN 300007
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

namespace toka
{
    template <typename T>
    struct edge_t
    {
        int adj, nxt;
        T w;
    };

    template <typename T>
    struct node_t
    {
        int i;
        T v;
    };

    template <typename Nd, typename Ed>
    class LinkGraph
    {
    private:
        int _n, _m;
        int _tail;
        std::shared_ptr<node_t<Nd>[]> _g;
        std::shared_ptr<edge_t<Ed>[]> _e;

    public:
        class EdgeSet
        {
        private:
            std::shared_ptr<edge_t<Ed>[]> _eptr;
            int _pos;

        public:
            class Iterator
            {
            private:
                int _pos;
                std::shared_ptr<edge_t<Ed>[]> _eptr;

            public:
                Iterator(std::shared_ptr<edge_t<Ed>[]> e_ptr, int pos)
                {
                    _eptr = e_ptr;
                    _pos = pos;
                }
                Iterator &operator++()
                {
                    _pos = _eptr[_pos].nxt;
                    return *this;
                }
                bool operator!=(const Iterator &other)
                {
                    return _pos != other._pos || _eptr.get() != other._eptr.get();
                }
                edge_t<Ed> &operator*()
                {
                    return _eptr[_pos];
                }
            };
            EdgeSet(std::shared_ptr<edge_t<Ed>[]> e_ptr, int pos)
            {
                _eptr = e_ptr;
                _pos = pos;
            }
            Iterator begin()
            {
                return Iterator(_eptr, _pos);
            }
            Iterator end()
            {
                return Iterator(_eptr, 0);
            }
        };
        class Iterator
        {
        private:
            int _pos = 0;
            LinkGraph *_ptr;

        public:
            Iterator(LinkGraph *G, int pos)
            {
                _ptr = G;
                _pos = pos;
            }

            Iterator &operator++()
            {
                _pos++;
                return *this;
            }
            bool operator!=(const Iterator &other)
            {
                return _ptr != other._ptr || _pos != other._pos;
            }
            node_t<Nd> &operator*()
            {
                return _ptr->_g[_pos];
            }
        };

        LinkGraph(const int &n, const int &m)
        {
            _n = n;
            _m = m;
            _g = static_cast<std::shared_ptr<node_t<Nd>[]>>(new node_t<Nd>[n]);
            _tail = 0;
            _e = static_cast<std::shared_ptr<edge_t<Ed>[]>>(new edge_t<Ed>[m + 1]);
            for (int i = 0; i < n; ++i)
                _g[i].i = 0;
        }

        edge_t<Ed> &add_edge(int x, int y)
        {
            ++_tail;
            _e[_tail].adj = y;
            _e[_tail].nxt = _g[x].i;
            _g[x].i = _tail;
            return _e[_tail];
        }

        edge_t<Ed> &add_edge(int x, int y, Ed w)
        {
            edge_t<Ed> &e = add_edge(x, y);
            e.w = w;
            return e;
        }

        Iterator begin()
        {
            return Iterator(this, 0);
        }

        Iterator end()
        {
            return Iterator(this, _n);
        }

        friend std::ostream &operator<<(std::ostream &stream, LinkGraph A)
        {
            stream << "[*LinkGraph* of " << A._n << " nodes and " << A._m << " edges (capacity)]";
            return stream;
        }

        node_t<Nd> &operator[](int pos)
        {
            return _g[pos];
        }

        EdgeSet get_edges(const node_t<Nd> &node)
        {
            return EdgeSet(_e, node.i);
        }

        size_t size()
        {
            return _n;
        }
    };
} // namespace toka

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

void dfs(toka::LinkGraph<int, int> &G, int x, VL &v, VI &tim, int &cnt)
{
    ++cnt;
    if (G[x].v)
        v[x] = 1;
    else
        v[x] = 0;
    for (auto &e : G.get_edges(G[x]))
    {
        if (G[e.adj].v == 0)
            continue;
        if (v[e.adj] == -1)
        {
            dfs(G, e.adj, v, tim, cnt);
            if (v[e.adj] == LINF)
            {
                v[x] = LINF;
            }
            else
            {
                v[x] = max(v[x], v[e.adj] + 1);
            }
        }
        else
        {
            if (tim[e.adj] == -1)
                v[x] = LINF;
            else
                v[x] = max(v[x], v[e.adj] + 1);
        }
    }
    tim[x] = cnt;
}

LL check(toka::LinkGraph<int, int> &G, const vector<PA> &q, int l)
{
    for (int i = 0; i <= l; ++i)
    {
        G[q[i].FST].v = 1;
    }
    for (int i = l + 1; i < q.size(); ++i)
    {
        G[q[i].FST].v = 0;
    }
    // for (int i = 1; i < G.size(); ++i)
    // {
    //     cerr << i << ": " << G[i].v << endl;
    // }
    VL v(G.size(), -1);
    VI tim(G.size(), -1);
    LL ans = 0;
    int cnt = 0;
    for (int i = 1; i < G.size(); ++i)
    {
        if (v[i] == -1 && G[i].v == 1)
        {
            dfs(G, i, v, tim, cnt);
        }
        if (G[i].v == 1)
            ans = max(ans, v[i]);
    }
    return ans;
}

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, m;
    LL k;

    cin >> n >> m >> k;
    read_array<int>(a + 1, n);
    vector<PA> q;
    q.clear();
    for (int i = 1; i <= n; ++i)
        q.pb(PA(i, a[i]));

    toka::LinkGraph<int, int> G(n + 1, m + 1);
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        G.add_edge(x, y);
    }
    auto mcmp = [](PA x, PA y) -> int
    { return x.SND < y.SND; };
    sort(q.begin(), q.end(), mcmp);
    VI inds;
    inds.clear();
    int prev = -1, cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (q[i].SND != prev)
        {
            if (cnt > 0)
            {
                inds.pb(i - 1);
            }
            cnt = 0;
            prev = q[i].SND;
        }
        cnt += 1;
    }
    inds.pb(n - 1);
    int l = -1, r = inds.size();
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        int o = inds[mid];
        LL d = check(G, q, o);
        // cerr << "o: " << o << " d: " << d << " (" << l << " " << r << endl;
        if (d >= k)
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }
    if (r == inds.size())
    {
        puts("-1");
    }
    else
    {
        printf("%d\n", q[inds[r]].SND);
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
