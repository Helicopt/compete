namespace toka
{
    template <typename T>
    struct edge_t
    {
        int from, i, nxt, pre;
        int adj;
        T w;
    };

    template <typename T>
    struct node_t
    {
        int i, ri;
        T v;
    };

    template <typename Nd, typename Ed>
    class LinkGraph
    {
    private:
        int _n, _m;
        int _tail;
        std::shared_ptr<std::vector<node_t<Nd>>> _g;
        std::shared_ptr<std::vector<edge_t<Ed>>> _e;

    public:
        class EdgeSet
        {
        private:
            std::shared_ptr<std::vector<edge_t<Ed>>> _eptr;
            int _pos, _rpos;

        public:
            class Iterator
            {
            private:
                int _pos;
                bool _revert;
                std::shared_ptr<std::vector<edge_t<Ed>>> _eptr;

            public:
                Iterator(std::shared_ptr<std::vector<edge_t<Ed>>> e_ptr, int pos, bool revert = false)
                {
                    _eptr = e_ptr;
                    _pos = pos;
                    _revert = revert;
                }
                Iterator &operator++()
                {
                    if (!_revert)
                        _pos = _eptr->at(_pos).nxt;
                    else
                        _pos = _eptr->at(_pos).pre;
                    return *this;
                }
                Iterator &operator--()
                {
                    if (_revert)
                        _pos = _eptr->at(_pos).nxt;
                    else
                        _pos = _eptr->at(_pos).pre;
                    return *this;
                }
                bool operator!=(const Iterator &other)
                {
                    return _pos != other._pos || _eptr.get() != other._eptr.get();
                }
                bool operator==(const Iterator &other)
                {
                    return _pos == other._pos && _eptr.get() == other._eptr.get();
                }
                edge_t<Ed> &operator*()
                {
                    return _eptr->at(_pos);
                }
            };
            EdgeSet(std::shared_ptr<std::vector<edge_t<Ed>>> e_ptr, int pos, int rpos)
            {
                _eptr = e_ptr;
                _pos = pos;
                _rpos = rpos;
            }
            Iterator begin()
            {
                return Iterator(_eptr, _pos);
            }
            Iterator end()
            {
                return Iterator(_eptr, 0);
            }
            Iterator rbegin()
            {
                return Iterator(_eptr, _rpos, true);
            }
            Iterator rend()
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
                return _ptr->_g->at(_pos);
            }
        };

        LinkGraph(const int n, const int m = 0)
        {
            _n = n;
            _m = m;
            _g = std::make_shared<std::vector<node_t<Nd>>>(n + 1);
            _tail = 0;
            _e = std::make_shared<std::vector<edge_t<Ed>>>(m + 1);
            for (int i = 0; i <= n; ++i)
            {
                (*_g)[i].i = 0;
                (*_g)[i].ri = 0;
            }
        }

        edge_t<Ed> &add_edge(int x, int y)
        {
            int ptr;
            ptr = ++_tail;
            auto &ev = *_e;
            auto &gv = *_g;
            if (_tail >= ev.size())
            {
                ev.push_back(edge_t<Ed>());
                _m = ev.size() - 1;
            }
            ev[ptr].from = x;
            ev[ptr].adj = y;
            ev[ptr].nxt = gv[x].i;
            ev[ptr].pre = 0;
            ev[ptr].i = ptr;
            if (gv[x].i > 0)
                ev[gv[x].i].pre = ptr;
            gv[x].i = ptr;
            if (gv[x].ri == 0)
                gv[x].ri = ptr;
            return ev[ptr];
        }

        edge_t<Ed> &add_edge(int x, int y, Ed w)
        {
            edge_t<Ed> &e = add_edge(x, y);
            e.w = w;
            return e;
        }

        bool del_edge(const edge_t<Ed> &edge)
        {

            auto &ev = *_e;
            auto &gv = *_g;
            auto &e = ev[edge.i];
            if (e.pre == 0 && e.nxt == 0)
                return false;
            if (e.pre > 0)
                ev[e.pre].nxt = e.nxt;
            else
                gv[e.from].i = e.nxt;
            if (e.nxt > 0)
                ev[e.nxt].pre = e.pre;
            else
                gv[e.from].ri = e.pre;

            e.pre = 0;
            e.nxt = 0;

            swap(ev[e.i], ev[_tail]);
            e.i = ev[_tail].i;
            ev[_tail].i = 0;
            --_tail;
            if (e.pre > 0)
                ev[e.pre].nxt = e.i;
            else
                gv[e.from].i = e.i;
            if (e.nxt > 0)
                ev[e.nxt].pre = e.i;
            else
                gv[e.from].ri = e.i;
            return true;
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
            stream << "[*LinkGraph* of " << A._n << " nodes and " << A._tail << " edges (capacity " << A._m << ")]";
            return stream;
        }

        node_t<Nd> &operator[](int pos)
        {
            return _g->at(pos);
        }

        EdgeSet get_edges(const node_t<Nd> &node)
        {
            return EdgeSet(_e, node.i, node.ri);
        }

        size_t size()
        {
            return _n;
        }
    };
} // namespace toka