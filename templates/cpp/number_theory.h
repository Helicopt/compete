namespace toka
{

    template <typename T, typename M>
    T secure_mod(T a, M b)
    {
        return (a < 0) ? ((b - (-a) % b) % b) : (a % b);
    }

    template <typename T>
    T gcd(T x, T y)
    {
        while (y > 0)
        {
            T r = x % y;
            x = y;
            y = r;
        }
        return x;
    }

    template <typename T>
    std::pair<T, std::pair<T, T>> extgcd(T a, T b)
    {
        T x = 0, y = 1;
        for (T u = 1, v = 0; a;)
        {
            T q = b / a;
            x -= q * u;
            std::swap(x, u);
            y -= q * v;
            std::swap(y, v);
            b -= q * a;
            std::swap(b, a);
        }
        return std::make_pair(b, std::make_pair(x, y));
    }

    template <typename T>
    std::pair<T, T> CRT(T x, T a, T y, T b)
    {
        // px+a = qy+b
        T d = abs(a - b);
        auto e = extgcd(x, y);
        if (d % e.first != 0)
        {
            return std::make_pair((T)0, (T)0);
        }
        else
        {
            // z % x == a
            // z % y == b
            T lcm = x / e.first * y;
            T k = d / e.first;
            if (a > b)
            {
                return std::make_pair((secure_mod(e.second.second, lcm) * k % lcm * y % lcm + b) % lcm, lcm);
            }
            else
            {
                return std::make_pair((secure_mod(e.second.first, lcm) * k % lcm * x % lcm + a) % lcm, lcm);
            }
            // e.second.first * k + y / e.first * t
            // e.second.second * k + x / e.first * t
        }
    }

    template <typename T>
    T lcm(T x, T y)
    {
        T g = gcd(x, y);
        assert(g != 0);
        return x * y / g;
    }

    template <typename T, typename M = unsigned long>
    T qpow(T a, LL b, T one, M m = 0)
    {
        T ret = one;
        T k = a;
        while (b)
        {
            if (b & 1)
                ret = ret * k;
            k = k * k;
            b >>= 1;
            if (m > 0)
            {
                k = k % m;
                ret = ret % m;
            }
        }
        return ret;
    }

    template <typename T, typename M = unsigned long>
    T qpow(T a, LL b, M m = 0)
    {
        return qpow(a, b, (T)1, m);
    }

    template <typename T, typename M>
    T inv(T a, T one, M m)
    {
        return qpow(a, m - 2, one, m);
    }

    template <typename T, typename M>
    T inv(T a, M m)
    {
        return qpow(a, m - 2, (T)1, m);
    }

    template <typename T, typename M>
    T inv_gen(T a, M m)
    {
        auto d = extgcd(a, m);
        if (1 % d.first != 0)
        {
            return (T)0;
        }
        else
        {
            return secure_mod(d.second.first, m);
        }
    }

    template <typename T, typename M>
    void get_facts(const unsigned long n, std::vector<T> &ret, T one, M m = 0)
    {
        ret.resize(n + 1, one);
        for (long long i = 2; i <= n; ++i)
        {
            ret[i] = i * ret[i - 1];
            if (m > 1)
                ret[i] %= m;
        }
    }

    template <typename T, typename M>
    void get_ifacts(const unsigned long n, std::vector<T> &ret, T one, M m)
    {
        ret.resize(n + 1, one);
        for (long long i = 2; i <= n; ++i)
        {
            ret[i] = inv(i, one, m) * ret[i - 1] % m;
        }
    }

    template <typename T, typename M>
    T CC(std::vector<T> &facts, std::vector<T> &ifacts, const unsigned long n, const unsigned long m, M mod)
    {
        if (m < 0 || m > n)
            return (T)0;
        return facts[n] * ifacts[n - m] % mod * ifacts[m] % mod;
    }

    void get_primes(const unsigned long n, VI &ret)
    {
        ret.clear();
        std::vector<bool> flags(n + 1, true);
        for (unsigned long i = 2; i <= n; ++i)
        {
            if (flags[i])
            {
                ret.emplace_back(i);
            }
            for (auto k : ret)
            {
                if ((LL)i * k > n)
                    break;
                flags[i * k] = false;
                if (i % k == 0)
                    break;
            }
        }
    }

    template <typename T, typename M>
    M divide_large(const std::vector<T> &n, M m, std::vector<T> &q, unsigned long long base = 10)
    {
        signed long L = n.size() - 1;
        unsigned long long cum = 0;
        q.clear();
        q.resize(n.size(), 0);
        while (L >= 0)
        {
            cum = cum * base + n[L];
            if (cum >= m)
            {
                q[L] = cum / m;
                cum = cum % m;
            }
            L -= 1;
        }
        L = n.size() - 1;
        while (L >= 0 && q[L] == 0)
        {
            q.pop_back();
            L -= 1;
        }
        return (M)cum;
    }

} // namespace toka