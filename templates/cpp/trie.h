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
            const VI *_seq;
            int _ind;

        public:
            Iterator(const VI &seq, TrieNode<T, maxsize> *root, int index = -1)
            {
                _ind = index;
                _pos = root;
                _seq = &seq;
            }
            Iterator &operator++()
            {
                _ind += 1;
                auto ind = (_ind < _seq->size()) ? (*_seq)[_ind] : -1;
                _pos = (ind >= 0) ? _pos->ch[ind] : nullptr;
                return *this;
            }
            bool operator!=(const Iterator &other)
            {
                return _pos != other._pos || _ind != other._ind;
            }
            T &operator*()
            {
                return _pos->data;
            }
        };
        TriePath(const VI &path, TrieNode<T, maxsize> *root)
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
            return Iterator(seq, nullptr, seq.size());
        }

    private:
        VI seq;
        TrieNode<T, maxsize> *_root;
    };

    template <typename T, size_t maxsize>
    class Trie
    {
        TrieNode<T, maxsize> root;

    public:
        void insert(const VI &seq, const T &data)
        {
            TrieNode<T, maxsize> *ptr = &root;
            int nxt = 0;
            while (nxt < seq.size())
            {
                auto ind = seq[nxt];
                if (ind < 0 || ind >= maxsize)
                {
                    throw std::runtime_error("index exceed error");
                }
                if (ptr->ch[ind] == nullptr)
                {
                    ptr->ch[ind] = new TrieNode<T, maxsize>();
                }
                ptr->ch[ind]->cnt += 1;
                if (nxt == seq.size() - 1)
                {
                    ptr->ch[ind]->ends += 1;
                }
                insert_update(nxt, ind, nxt == seq.size() - 1, ptr->ch[ind]->data, data);
                ptr = ptr->ch[ind];
                nxt += 1;
            }
        }

        void remove(const VI &seq, const T &data)
        {
            TrieNode<T, maxsize> *ptr = &root;
            int nxt = 0;
            while (nxt < seq.size())
            {
                auto ind = seq[nxt];
                if (ind < 0 || ind >= maxsize)
                {
                    throw std::runtime_error("index exceed error");
                }
                if (ptr->ch[ind] == nullptr)
                {
                    return;
                }
                ptr->ch[ind]->cnt -= 1;
                if (nxt == seq.size() - 1)
                {
                    ptr->ch[ind]->ends -= 1;
                }
                remove_update(nxt, ind, nxt == seq.size() - 1, ptr->ch[ind]->data, data);
                ptr = ptr->ch[ind];
                nxt += 1;
            }
        }

        TriePath<T, maxsize> search(const VI &path)
        {
            return TriePath<T, maxsize>(path, &root);
        }

    private:
        void insert_update(int ind, int val, bool is_end, T &node, const T &data)
        {
            node += data;
        }
        void remove_update(int ind, int val, bool is_end, T &node, const T &data)
        {
            node -= data;
        }
    };
} // namespace toka