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