namespace toka
{
    template <typename Nd, typename Ed, typename T>
    std::vector<T> spfa(LinkGraph<Nd, Ed> &G, int src, T zero, T inf, T (*dist)(edge_t<Ed>) = nullptr)
    {
        if (dist == nullptr)
            dist = [](edge_t<Ed> _e) -> T
            { return (T)_e.w; };
        std::vector<T> D(G.size() + 1, inf);
        D[src] = zero;
        std::vector<bool> inq(G.size() + 1, false);
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

namespace toka
{
    template <typename Nd, typename Ed, typename T>
    std::vector<T> dijkstra(LinkGraph<Nd, Ed> &G, int src, T zero, T inf, T (*dist)(edge_t<Ed>) = nullptr)
    {
        if (dist == nullptr)
            dist = [](edge_t<Ed> _e) -> T
            { return (T)_e.w; };
        std::vector<T> D(G.size() + 1, inf);
        D[src] = zero;
        std::priority_queue<std::pair<T, int>> q;
        q.push(std::make_pair(zero, src));
        while (!q.empty())
        {
            auto p = q.top();
            q.pop();
            if (-p.first != D[p.second])
                continue;
            auto &node = G[p.second];
            for (auto &e : G.get_edges(node))
            {
                T _d = D[p.second] + dist(e);
                if (_d < D[e.adj])
                {
                    D[e.adj] = _d;
                    q.push(std::make_pair(-D[e.adj], e.adj));
                }
            }
        }
        return D;
    }
} // namespace toka
