namespace toka
{
    template <typename T>
    class Matrix
    {
    private:
        unsigned int _h, _w;
        std::shared_ptr<T[]> _d;
        void _allocate(unsigned int h, unsigned int w)
        {
            _h = h;
            _w = w;
            _d = static_cast<std::shared_ptr<T[]>>(new T[_h * _w]);
        }

    public:
        Matrix(unsigned int h, unsigned int w)
        {
            _allocate(h, w);
        }
        Matrix(unsigned int h, unsigned int w, const T &fill_)
        {
            _allocate(h, w);
            for (size_t i = 0; i < _h * _w; ++i)
                _d[i] = fill_;
        }

        Matrix copy()
        {
            Matrix ret = Matrix(_h, _w, 0);
            for (size_t i = 0; i < _h * _w; ++i)
            {
                ret._d[i] = _d[i];
            }
            // memcpy(ret._d.get(), _d.get(), _h * _w * sizeof(T));
            return ret;
        }

        T &operator[](PA index)
        {
            return _d[index.first * _w + index.second];
        }

        friend std::ostream &operator<<(std::ostream &stream, Matrix A)
        {
            VI width;
            for (unsigned int i = 0; i < A._w; ++i)
            {
                size_t tmp = 0;
                for (unsigned int j = 0; j < A._h; ++j)
                {
                    T k = A[PA(j, i)];
                    std::stringstream ts;
                    ts << k;
                    std::string s = ts.str();
                    tmp = std::max(tmp, s.length());
                }
                width.emplace_back(tmp);
            }
            for (unsigned int i = 0; i < A._h; ++i)
            {
                stream << "[";
                for (unsigned int j = 0; j < A._w; ++j)
                {
                    T k = A[PA(i, j)];
                    std::stringstream ts;
                    ts << k;
                    std::string s = ts.str();
                    while (s.length() < width[j] + 2)
                        s = " " + s;
                    stream << s;
                }
                stream << " ]" << std::endl;
            }
            stream << "(Matrix of " << A._h << "x" << A._w << ")";
            return stream;
        }

        Matrix ONE()
        {
            Matrix ret = Matrix(_h, _w, 0);
            for (unsigned int i = 0; i < std::min(_h, _w); ++i)
            {
                ret[PA(i, i)] = 1;
            }
            return ret;
        }

        static Matrix ONE(unsigned int n)
        {
            Matrix ret = Matrix(n, n, 0);
            for (unsigned int i = 0; i < n; ++i)
            {
                ret[PA(i, i)] = 1;
            }
            return ret;
        }

        Matrix _add(Matrix other)
        {
            assert(_h == other._h && _w == other._w);
            for (unsigned int i = 0; i < _h; ++i)
            {
                for (unsigned int j = 0; j < _w; ++j)
                {
                    operator[](PA(i, j)) += other[PA(i, j)];
                }
            }
            return *this;
        }

        Matrix operator+(Matrix other)
        {
            assert(_h == other._h && _w == other._w);
            auto ret = copy();
            ret._add(other);
            return ret;
        }

        Matrix _mul(Matrix other, Matrix dst)
        {
            assert(_h == other._h && _w == other._w && _w == other._w);
            assert(dst._h = _h && dst._w == other._w);
            for (unsigned int i = 0; i < _h; ++i)
            {
                for (unsigned int j = 0; j < other._w; ++j)
                {
                    dst[PA(i, j)] = 0;
                    for (unsigned int k = 0; k < _w; ++k)
                    {
                        dst[PA(i, j)] += operator[](PA(i, k)) * other[PA(k, j)];
                    }
                }
            }
            return dst;
        }

        Matrix operator*(Matrix other)
        {
            assert(_w == other._h);
            auto ret = Matrix(_h, other._w, 0);
            this->_mul(other, ret);
            return ret;
        }

        Matrix _mod(T mod)
        {
            for (unsigned int i = 0; i < _h; ++i)
            {
                for (unsigned int j = 0; j < _w; ++j)
                {
                    operator[](PA(i, j)) %= mod;
                }
            }
            return *this;
        }

        Matrix operator%(T mod)
        {
            auto ret = copy();
            ret._mod(mod);
            return ret;
        }
    };
} // namespace toka