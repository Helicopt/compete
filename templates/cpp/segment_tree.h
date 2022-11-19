namespace toka
{
    template <typename T>
    class SegTree
    {
    private:
        int _l, _r;
        std::shared_ptr<T[]> _d;

        virtual void _update(int l, int r, T &d, const T &c) = 0;
        virtual void _push(int l, int r, T &d, const T &c) = 0;
        virtual void _clear(int l, int r, T &d) = 0;
        virtual void _pull(int l, int m, int r, T &d, const T &lv, const T &rv) = 0;
        virtual T _merge(int l, int m, int r, const T &lv, const T &rv) = 0;

        void _insert(int u, int l, int r, int x, int y, const T &c)
        {
            if (l > r || x > y || x > r || y < l)
                return;
            x = std::max(x, l);
            y = std::min(y, r);
            if (l == x && r == y)
            {
                _update(l, r, _d[u], c);
                return;
            }
            int ll = u << 1, rr = ll + 1;
            int m = l + r >> 1;
            _push(l, m, _d[ll], _d[u]);
            _push(m + 1, r, _d[rr], _d[u]);
            _clear(l, r, _d[u]);
            if (y <= m)
                _insert(ll, l, m, x, y, c);
            else if (x > m)
                _insert(rr, m + 1, r, x, y, c);
            else
            {
                _insert(ll, l, m, x, m, c);
                _insert(rr, m + 1, r, m + 1, y, c);
            }
            _pull(l, m, r, _d[u], _d[ll], _d[rr]);
        }

        T _find(int u, int l, int r, int x, int y, const T &c)
        {
            if (l > r || x > y || x > r || y < l)
                return c;
            x = std::max(x, l);
            y = std::min(y, r);
            if (l == x && r == y)
            {
                return _d[u];
            }
            int ll = u << 1, rr = ll + 1;
            int m = l + r >> 1;
            _push(l, m, _d[ll], _d[u]);
            _push(m + 1, r, _d[rr], _d[u]);
            _clear(l, r, _d[u]);
            T ret;
            if (y <= m)
                ret = _find(ll, l, m, x, y, c);
            else if (x > m)
                ret = _find(rr, m + 1, r, x, y, c);
            else
            {
                auto lv = _find(ll, l, m, x, m, c);
                auto rv = _find(rr, m + 1, r, m + 1, y, c);
                ret = _merge(l, m, r, lv, rv);
            }
            _pull(l, m, r, _d[u], _d[ll], _d[rr]);
            return ret;
        }

    public:
        SegTree(int l, int r)
        {
            assert(l <= r);
            _l = l;
            _r = r;
            _d = static_cast<std::shared_ptr<T[]>>(new T[(_r - _l + 1) << 2]);
        }

        size_t size()
        {
            return _r - _l + 1;
        }

        void init(const T &c)
        {
            for (int i = 0; i < (size() << 2); ++i)
            {
                _d[i] = c;
            }
        }

        void insert(int l, int r, const T &c)
        {
            _insert(1, _l, _r, l, r, c);
        }

        void insert(int l, const T &c)
        {
            insert(l, l, c);
        }

        T find(int l, int r, const T &c)
        {
            return _find(1, _l, _r, l, r, c);
        }

        T find(int l, const T &c)
        {
            return find(l, l, c);
        }
    };

    struct SumSegTreeNode
    {
        int tag;
        int sum;
    };

    template <typename T>
    class _SumSegTree : public toka::SegTree<T>
    {
    private:
        void _update(int l, int r, T &d, const T &c)
        {
            d.tag += c.tag;
            d.sum += c.tag * (r - l + 1);
        }

        void _push(int l, int r, T &d, const T &c)
        {
            _update(l, r, d, c);
        }
        void _clear(int l, int r, T &d)
        {
            d.tag = 0;
        }
        void _pull(int l, int m, int r, T &d, const T &lv, const T &rv)
        {
            d.sum = lv.sum + rv.sum;
        }
        T _merge(int l, int m, int r, const T &lv, const T &rv)
        {
            T ret;
            _pull(l, m, r, ret, lv, rv);
            return ret;
        }

    public:
        using toka::SegTree<T>::SegTree;
    };

    class SumSegTree : public _SumSegTree<SumSegTreeNode>
    {
    public:
        using _SumSegTree::_SumSegTree;
    };
} // namespace toka