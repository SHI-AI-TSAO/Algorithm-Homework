// referance: https://zhuanlan.zhihu.com/p/144384951
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <numeric>

long long int topdown(std::vector<std::vector<long long int>> &dp, std::vector<std::vector<long long int>> &gcdt, int first, int last)
{
    if (dp[first][last] != 0)
        return dp[first][last];
    if ((last - first + 1) == 3) // base case
    {
        if ((gcdt[first][first + 1] > 1) && (gcdt[first + 1][last] > 1) && (gcdt[first][last] > 1))
            dp[first][last] = gcdt[first][first + 1] + gcdt[first + 1][last];
        else
            dp[first][last] = -1;
    }
    else if ((last - first + 1) == 2) // base case
    {
        if (gcdt[first][last] > 1)
            dp[first][last] = gcdt[first][last];
        else
            dp[first][last] = -1;
    }
    else
    {
        long long int maxnum = 0;
        long long int temp = 0;
        //(aaaa)(aaaa)
        for (int k = first; k <= (last - 1); ++k) // two sub sequence
        {
            if (dp[first][k] == 0)
                dp[first][k] = topdown(dp, gcdt, first, k);

            if (dp[k + 1][last] == 0)
                dp[k + 1][last] = topdown(dp, gcdt, k + 1, last);

            if ((dp[first][k] != -1) && (dp[k + 1][last] != -1))
            {
                temp = dp[first][k] + dp[k + 1][last];
                if (temp > maxnum)
                    maxnum = temp;
            }
        }

        // a(aaaa)a
        if (gcdt[first][last] > 1) // have to be concerned
        {
            if ((first + 1) <= (last - 1)) // at least three point
            {
                if (dp[first + 1][last - 1] == 0)
                    dp[first + 1][last - 1] = topdown(dp, gcdt, first + 1, last - 1);
                if (dp[first + 1][last - 1] != -1)
                {
                    temp = gcdt[first][last] + dp[first + 1][last - 1];
                    if (temp > maxnum)
                        maxnum = temp;
                }
            }
            else // just two point
            {
                temp = gcdt[first][last];
                if (temp > maxnum)
                    maxnum = temp;
            }
        }
        // aa(aa)a
        if ((first + 2) < (last - 1))
        {
            if ((gcdt[first][first + 1] > 1) && (gcdt[first + 1][last] > 1) && (gcdt[first][last] > 1))
            {
                if (dp[first + 2][last - 1] == 0)
                    dp[first + 2][last - 1] = topdown(dp, gcdt, first + 2, last - 1);
                if (dp[first + 2][last - 1] != -1)
                {
                    temp = dp[first + 2][last - 1] + gcdt[first][first + 1] + gcdt[first + 1][last];
                    if (temp > maxnum)
                        maxnum = temp;
                }
            }
        }
        // a(aa)aa
        if ((first + 1) < (last - 2))
        {
            if ((gcdt[first][last - 1] > 1) && (gcdt[last - 1][last] > 1) && (gcdt[first][last] > 1))
            {
                if (dp[first + 1][last - 2] == 0)
                    dp[first + 1][last - 2] = topdown(dp, gcdt, first + 1, last - 2);
                if (dp[first + 1][last - 2] != -1)
                {
                    temp = dp[first + 1][last - 2] + gcdt[first][last - 1] + gcdt[last - 1][last];
                    if (temp > maxnum)
                        maxnum = temp;
                }
            }
        }

        // a(aa)a(aa)a
        for (int k = (first + 3); k <= (last - 3); ++k) // two sub sequence
        {
            if ((gcdt[first][k] > 1) && (gcdt[k][last] > 1) && (gcdt[first][last] > 1)) // have to be concerned
            {
                if (dp[first + 1][k - 1] == 0)
                    dp[first][k] = topdown(dp, gcdt, first, k);
                if (dp[k + 1][last - 1] == 0)
                    dp[k + 1][last - 1] = topdown(dp, gcdt, k + 1, last - 1);
                if ((dp[first + 1][k - 1] != -1) && (dp[k + 1][last - 1] != -1))
                {
                    temp = dp[first + 1][k - 1] + dp[k + 1][last - 1] + gcdt[first][k] + gcdt[k][last];
                    if (temp > maxnum)
                        maxnum = temp;
                }
            }
        }

        if (maxnum > 0)
            dp[first][last] = maxnum;
        else
            dp[first][last] = -1;
    }
    // printf("(%d,%d) = %lld\n", first, last, dp[first][last]);
    return dp[first][last];
}

int main()
{
    int N;
    scanf("%d", &N);
    int a[N + 1];
    std::vector<std::vector<long long int>> dp(N, std::vector<long long int>(N, 0));
    for (int i = 0; i < (N - 1); ++i)
        scanf("%d ", &a[i]);
    scanf("%d", &a[N - 1]);
    // initialize dp
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (i == j)
                dp[i][j] = -1;
            else
                dp[i][j] = 0;
        }
    std::vector<std::vector<long long int>> gcdt(N, std::vector<long long int>(N, 0));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            gcdt[i][j] = (long long int)std::gcd(a[i], a[j]);
    dp[0][N - 1] = topdown(dp, gcdt, 0, N - 1);
    printf("%lld", dp[0][N - 1]);
    return 0;
}