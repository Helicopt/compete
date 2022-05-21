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

namespace toka
{
    template <typename Nd, typename Ed, typename T>
    std::vector<T> spfa(LinkGraph<Nd, Ed> &G, int src, T zero, T inf, T (*dist)(edge_t<Ed>) = nullptr)
    {
        if (dist == nullptr)
            dist = [](edge_t<Ed> _e) -> T
            { return (T)_e.w.SND; };
        std::vector<T> D(G.size(), inf);
        D[src] = zero;
        std::vector<bool> inq(G.size(), false);
        std::queue<int> q;
        q.push(src);
        inq[src] = true;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            inq[x] = false;
            auto &node = G[x];
            for (auto &e : G.get_edges(node))
            {
                T _d = D[x] + dist(e);
                if (_d < D[e.adj])
                {
                    D[e.adj] = _d;
                    if (!inq[e.adj])
                    {
                        q.push(e.adj);
                        inq[e.adj] = true;
                    }
                }
            }
        }
        return D;
    }
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

int getF(VI &q, int x)
{
    if (q[x] == x)
        return x;
    return q[x] = getF(q, q[x]);
}

void dfs(toka::LinkGraph<int, PA> G, int x, const VL &d, VI &vis, VI &ansq)
{
    vis[x] = 1;
    for (auto e : G.get_edges(G[x]))
    {
        if (vis[e.adj] == 0 && e.w.SND == d[e.adj] - d[x])
        {
            ansq.pb(e.w.FST);
            dfs(G, e.adj, d, vis, ansq);
        }
    }
}

void solve(int Ti)
{
    // printf("Case #%d:", Ti); // print the case number

    int n, m;

    scanf("%d%d", &n, &m);
    vector<VI> e;
    toka::LinkGraph<int, PA> G(n + 1, m * 3);
    for (int i = 0; i < m; ++i)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        G.add_edge(x, y, PA(i + 1, z));
        G.add_edge(y, x, PA(i + 1, z));
        e.pb({x, y, z});
    }
    auto dis = toka::spfa<int, PA, LL>(G, 1, 0, (LL)n * 1000000007);
    int cnt = 0;
    VI ansq;
    VI vis(n + 1, 0);
    dfs(G, 1, dis, vis, ansq);
    if (ansq.size() != n - 1)
        exit(1);
    for (int i = 0; i < ansq.size(); ++i)
    {
        printf("%d", ansq[i]);
        if (i != ansq.size() - 1)
            printf(" ");
    }
    printf("\n");
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
