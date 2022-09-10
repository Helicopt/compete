struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

long long mm[4] = {1007552461, 1221726697, 909939647, 911580793};
long long pp[4] = {868405243, 991737359, 818188841, 730379011};

template <size_t D>
class RollingHash
{

public:
    struct HashP
    {
        long long d[D];
        bool operator==(const HashP &other) const
        {
            for (int j = 0; j < D; ++j)
                if (d[j] != other.d[j])
                    return false;
            return true;
        }
    };

    template <typename T>
    void calc(T *x, int n, HashP *hx) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        memset(hx[0].d, 0, sizeof(hx[0].d));
        for (int i = 0; i < n; ++i)
        {
            auto tmp = hx[i];
            for (int j = 0; j < D; ++j)
                tmp.d[j] = (tmp.d[j] * pp[j] % mm[j] + x[i] + FIXED_RANDOM % mm[j]) % mm[j];
            hx[i + 1] = tmp;
        }
    }

    HashP hash(HashP *hx, int l, int r) const
    {
        auto tmp = hx[r];
        for (int j = 0; j < D; ++j)
            tmp.d[j] = (tmp.d[j] + mm[j] - hx[l - 1].d[j] * toka::qpow(pp[j], (r - l + 1), 1ll, mm[j]) % mm[j]) % mm[j];
        return tmp;
    }
};
