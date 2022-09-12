#include <bits/stdc++.h>
#include <pthread.h>
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
#define INFO(fmt, ...)                                                   \
    {                                                                    \
        fprintf(stderr, "rk%d/%d: %d] ", rank, world_size, thread_case); \
        fprintf(stderr, fmt, ##__VA_ARGS__);                             \
    }
#define MINFO(fmt, ...) \
    if (rank == 0)      \
    INFO(fmt, ##__VA_ARGS__)

using namespace std;

typedef long long LL;
typedef pair<int, int> PA;
typedef pair<LL, LL> PL;
typedef std::vector<int> VI;
typedef std::vector<long long> VL;

/*
{{libs}}
*/

class InputOut
{
private:
    int case_id;

    template <typename T>
    inline void read_array(vector<T> &a_, int n)
    {
        for (int i = 0; i < n; ++i)
        {
            int x;
            scanf("%d", &x);
            a_.pb((T)x);
        }
    }

public:
    // Input Field
    int n, k, d;
    vector<PA> a;

    // Output Field
    LL ans;

    InputOut(int caseno)
    {
        case_id = caseno;
        read();
    }

    void read()
    {
        scanf("%d%d%d", &n, &k, &d);
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            a.pb(PA(x, y));
        }
    }

    void write()
    {
        printf("Case #%d: ", case_id);
        if (ans == LINF)
            printf("-1\n");
        else
            printf("%lld\n", ans);
    }
};
namespace toka
{
    template <typename T>
    T dijkstra(const vector<PA> &b, int n, int src, int k, int d, T zero, T inf)
    {
        auto dist = [&](T _d) -> T
        { return max((T)k, _d); };
        auto dist2 = [](PA s, PA t) -> T
        { return (T)(s.FST - t.FST) * (s.FST - t.FST) + (T)(s.SND - t.SND) * (s.SND - t.SND); };
        set<int> valid;
        std::vector<T> D(n, inf);
        // for (int i = 0; i < n; ++i)
        //     D[i] = inf;
        D[src] = zero;
        // std::priority_queue<std::pair<T, int>> q;
        // q.push(std::make_pair(zero, src));
        for (int i = 0; i < n; ++i)
            valid.insert(i);
        for (int _ = 0; _ < n; ++_)
        {
            T mini = inf;
            int mini_ind = -1;
            for (int j : valid)
            {
                if (D[j] < mini)
                {
                    mini = D[j];
                    mini_ind = j;
                }
            }
            if (mini_ind == -1)
                return inf;
            auto p = make_pair(mini, mini_ind);
            valid.erase(p.second);
            if (p.second == n - 1)
                return D[n - 1];
            // if (-p.first != D[p.second])
            //     continue;
            auto &node = b[p.second];
            for (int i : valid)
            {
                T __d = dist2(node, b[i]);
                if ((T)d * d < __d)
                    continue;
                T _d = D[p.second] + dist(__d);
                if (_d < D[i])
                {
                    D[i] = _d;
                    // q.push(std::make_pair(-D[i], i));
                }
            }
        }
        return D[n - 1];
    }
} // namespace toka

void solve(InputOut *inout, int rank, int world_size, int thread_case)
{
    auto &ans = inout->ans;
    auto &a = inout->a;
    auto &n = inout->n;
    auto &k = inout->k;
    auto &d = inout->d;

    sort(a.BE, a.ED);

    int m = 1;

    VI xaxis(0);
    xaxis.pb(a[0].FST);
    a[0] = PA(a[0].SND, a[0].SND);

    for (int i = 1; i < n - 1; ++i)
    {
        int x = a[i].FST;
        int b = a[i].SND;
        while (i + 1 < n - 1 && a[i + 1].FST == x)
        {
            ++i;
        }
        int t = a[i].SND;
        xaxis.pb(x);
        a[m++] = PA(b, t);
    }
    xaxis.pb(a[n - 1].FST);
    a[m] = PA(a[n - 1].SND, a[n - 1].SND);
    vector<int> top, bot;
    top.pb(0);
    bot.pb(0);
    for (int i = 1; i <= m; ++i)
    {
        while (bot.size() >= 2)
        {
            PL k_b = PL(a[i].FST - a[bot[bot.size() - 2]].FST, xaxis[i] - xaxis[bot[bot.size() - 2]]);
            PL k_b_pre = PL(a[bot.back()].FST - a[bot[bot.size() - 2]].FST, xaxis[bot.back()] - xaxis[bot[bot.size() - 2]]);
            if (k_b.FST * k_b_pre.SND <= k_b_pre.FST * k_b.SND)
            {
                bot.pop_back();
            }
            else
                break;
        }
        bot.push_back(i);
    }
    for (int i = 1; i <= m; ++i)
    {
        while (top.size() >= 2)
        {
            PL k_b = PL(a[i].SND - a[top[top.size() - 2]].SND, xaxis[i] - xaxis[top[top.size() - 2]]);
            PL k_b_pre = PL(a[top.back()].SND - a[top[top.size() - 2]].SND, xaxis[top.back()] - xaxis[top[top.size() - 2]]);
            if (k_b.FST * k_b_pre.SND >= k_b_pre.FST * k_b.SND)
            {
                top.pop_back();
            }
            else
                break;
        }
        top.push_back(i);
    }
    m = 0;
    vector<PA> b;
    // set<PA> ss;
    for (int i : bot)
    {
        b.pb(PA(xaxis[i], a[i].FST));
        // cout << xaxis[i] << "," << a[i].FST << " ";
    }
    // cout << endl;
    for (int i : top)
    {
        b.pb(PA(xaxis[i], a[i].SND));
        // cout << xaxis[i] << "," << a[i].SND << " ";
    }
    // cout << endl;
    sort(b.BE, b.ED);
    m = unique(b.BE, b.ED) - b.BE;
    n = m;
    // for (auto p : ss)
    // {
    //     a[n++] = p;
    // }
    // cerr << n << " " << bot.size() << " " << top.size() << endl;
    ans = toka::dijkstra<LL>(b, n, 0, k, d, 0ll, LINF);
}

struct arg_t
{
    int rank;
    int world_size;
    int n;
    InputOut **in_out;
};

void *thread_run(void *args_)
{
    auto args = (arg_t *)args_;
    int rank = args->rank;
    int world_size = args->world_size;
    int n = args->n;
    for (int tcase = 0; tcase < n; ++tcase)
    {
        solve(args->in_out[tcase], rank, world_size, tcase);
    }
    return NULL;
}

const int NUM_THREADS = 8;

pthread_t threads[NUM_THREADS];
arg_t args[NUM_THREADS];

int main()
{
    int T = 1;
    vector<InputOut *> data(0);
    VI inds(0);
    scanf("%d", &T); // number of test cases
    for (int Ti = 1; Ti <= T; Ti++)
    {
        auto inout = new InputOut(Ti);
        data.pb(inout);
        inds.pb(Ti - 1);
    }

    random_shuffle(inds.begin(), inds.end());
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        size_t S = (inds.size() + NUM_THREADS - 1) / NUM_THREADS;
        size_t be = i * S;
        size_t en = min(be + S, inds.size());
        args[i].rank = i;
        args[i].world_size = NUM_THREADS;
        args[i].n = en - be;
        if (args[i].n <= 0)
            continue;
        cerr << "Launched " << i << ": " << args[i].n << endl;
        auto pmem = new InputOut *[args[i].n];
        args[i].in_out = pmem;
        for (int j = 0; j < args[i].n; ++j)
        {
            args[i].in_out[j] = data[inds[be + j]];
        }
        int t = pthread_create(threads + i, NULL, thread_run, (void *)(args + i));
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        if (args[i].n > 0)
        {
            pthread_join(threads[i], NULL);
            delete[] args[i].in_out;
            cerr << "Finished " << i << endl;
        }
    }

    for (auto d : data)
    {
        d->write();
        delete d;
    }
    data.clear();
    return 0;
}
