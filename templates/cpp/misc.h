void kmp(char *s, size_t n, VI &fail)
{
    fail.resize(n + 1);
    fail[0] = fail[1] = 0;
    int i = 1, j = 0;
    while (i < n)
    {
        if (s[i] == s[j])
        {
            ++i;
            ++j;
            fail[i] = j;
        }
        else if (j == 0)
        {
            ++i;
            fail[i] = j;
        }
        else
            j = fail[j];
    }
}
