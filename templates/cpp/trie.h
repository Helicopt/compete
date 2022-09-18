namespace toka
{
    template <typename T, size_t maxsize>
    struct TrieNode
    {
        size_t MAXSIZE = maxsize;
        T data;
        size_t cnt, ends;
        TrieNode<T, maxsize> *ch[maxsize];
        TrieNode()
        {
            memset(ch, 0, sizeof(ch));
            reset();
        }
        void reset()
        {
            cnt = 0;
            ends = 0;
            free();
        }
        void free()
        {
            for (size_t i = 0; i < maxsize; ++i)
            {
                if (ch[i] != nullptr)
                {
                    ch[i]->free();
                }
            }
            memset(ch, 0, sizeof(ch));
        }
        ~TrieNode()
        {
            free();
        }
    };

    template <typename T, size_t maxsize>
    class TriePath
    {
    public:
        class Iterator
        {
        private:
            TrieNode<T, maxsize> *_pos;
            const vector<int> *_seq;
            int _ind;

        public:
            Iterator(const vector<int> &seq, TrieNode<T, maxsize> *root, int index = 0)
            {
                _ind = index;
                _pos = root;
                _seq = &seq;
            }
            Iterator &operator++()
            {
                auto ind = (_ind < _seq->size()) ? (*_seq)[_ind] : -1;
                _ind = min(_ind + 1, (int)_seq->size() + 1);
                _pos = (ind >= 0) ? _pos->ch[ind] : nullptr;
                return *this;
            }
            bool operator!=(const Iterator &other)
            {
                return _pos != other._pos || _ind != other._ind;
            }
            pair<pair<size_t, size_t>, T &> operator*()
            {
                return make_pair<pair<size_t, size_t>, reference_wrapper<T>>(make_pair(_pos->cnt, _pos->ends), _pos->data);
            }
        };
        TriePath(const vector<int> &path, TrieNode<T, maxsize> *root)
        {
            seq = path;
            _root = root;
        }
        Iterator begin()
        {
            return Iterator(seq, _root);
        }
        Iterator end()
        {
            return Iterator(seq, nullptr, seq.size() + 1);
        }

    private:
        vector<int> seq;
        TrieNode<T, maxsize> *_root;
    };

    template <typename T, size_t maxsize>
    class Trie
    {
        TrieNode<T, maxsize> root;

    public:
        void insert(const vector<int> &seq, const T &data)
        {
            TrieNode<T, maxsize> *ptr = &root;
            int nxt = 0;
            while (1)
            {
                ++ptr->cnt;
                if (nxt == seq.size())
                {
                    ++ptr->ends;
                }
                insert_update(nxt, seq, nxt == seq.size(), ptr->data, data);
                if (nxt >= seq.size())
                    break;
                auto ind = seq[nxt];
                if (ind < 0 || ind >= maxsize)
                {
                    throw std::runtime_error("index exceed error");
                }
                if (ptr->ch[ind] == nullptr)
                {
                    ptr->ch[ind] = new TrieNode<T, maxsize>();
                }
                ptr = ptr->ch[ind];
                nxt += 1;
            }
        }

        size_t count(const vector<int> &seq, bool end = true)
        {
            TrieNode<T, maxsize> *ptr = &root;
            int nxt = 0;
            while (1)
            {
                if (nxt == seq.size())
                {
                    if (end)
                        return ptr->ends;
                    else
                        return ptr->cnt;
                }
                auto ind = seq[nxt];
                if (ind < 0 || ind >= maxsize)
                {
                    throw std::runtime_error("index exceed error");
                }
                if (ptr->ch[ind] == nullptr)
                {
                    return 0;
                }
                ptr = ptr->ch[ind];
                nxt += 1;
            }
        }

        void remove(const vector<int> &seq, const T &data)
        {
            TrieNode<T, maxsize> *ptr = &root;
            int nxt = 0;
            vector<TrieNode<T, maxsize>> q;
            bool found = true;
            while (1)
            {
                q.push_back(ptr);
                // --ptr->cnt;
                // if (nxt == seq.size()) {
                //     --ptr->ends;
                // }
                // remove_update(nxt, seq, nxt == seq.size(), ptr->data, data);
                if (nxt >= seq.size())
                    break;
                auto ind = seq[nxt];
                if (ind < 0 || ind >= maxsize)
                {
                    throw std::runtime_error("index exceed error");
                }
                if (ptr->ch[ind] == nullptr)
                {
                    found = false;
                    return;
                }
                ptr = ptr->ch[ind];
                nxt += 1;
            }
            if (found)
            {
                for (int i = 0; i < q.size(); ++i)
                {
                    auto p = q[i];
                    --p->cnt;
                    remove_update(i, seq, i == q.size() - 1, p->data, data);
                }
                --q.back()->ends;
            }
        }

        TriePath<T, maxsize> search(const vector<int> &path)
        {
            return TriePath<T, maxsize>(path, &root);
        }

    private:
        void insert_update(int ind, const vector<int> &seq, bool is_end, T &node, const T &data)
        {
            node += data;
        }
        void remove_update(int ind, const vector<int> &seq, bool is_end, T &node, const T &data)
        {
            node -= data;
        }
    };
} // namespace toka