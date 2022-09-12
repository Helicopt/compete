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
    int n;
    VI a;

    // Output Field
    int ans;

    InputOut(int caseno)
    {
        case_id = caseno;
        read();
    }

    void read()
    {
        scanf("%d", &n);
        read_array(a, n);
    }

    void write()
    {
        printf("Case #%d:", case_id);
        printf(" %d\n", ans);
    }
};

void solve(InputOut *inout, int rank, int world_size, int thread_case)
{
    int &ans = inout->ans;
    VI &a = inout->a;
    ans = 0;
    MINFO("%u\n", a.size())
    for (int i = 0; i < inout->n; ++i)
    {
        ans += a[i];
    }
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
