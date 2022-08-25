// referance: https://zhuanlan.zhihu.com/p/144384951
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <numeric>

int main()
{
    int N;
    scanf("%d", &N);
    int a[N + 1];
    long long int dp[N][N];
    for (int i = 0; i < (N - 1); ++i)
        scanf("%d ", &a[i]);
    scanf("%d", &a[N - 1]);
    // initialize dp
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j)
        {
            if (i == j)
                dp[i][j] = -1;
            else
                dp[i][j] = 0;
        }
    // gcd table
    long long int gcdt[N][N];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            gcdt[i][j] = (long long int)std::gcd(a[i], a[j]);

    // dp from bottom to top, from left to right
    long long int maxnum = 0;
    long long int temp = 0;
    int pair = 0;
    for (int i = (N - 2); i >= 0; --i)
    {
        for (int j = i + 1; j <= (N - 1); ++j)
        {
            maxnum = 0;
            temp = 0;
            pair = 0;
            for (int k1 = i; k1 <= j - 1; ++k1) // two sub sequence
            {
                if ((dp[i][k1] != -1) && (dp[k1 + 1][j] != -1))
                {
                    pair = 1;
                    temp = dp[i][k1] + dp[k1 + 1][j];
                    if (temp > maxnum)
                        maxnum = temp;
                }
            }

            // two point: first and last
            if ((gcdt[i][j] > 1) && (dp[i + 1][j - 1] != -1))
            {
                pair = 1;
                temp = (long long int)gcdt[i][j] + dp[i + 1][j - 1];
                if (temp > maxnum)
                    maxnum = temp;
            }

            // three point: first and middle and last (i,k1,j)
            for (int k1 = (i + 1); k1 <= (j - 1); ++k1)
            {
                if ((dp[i + 1][k1 - 1] != (long long int)-1) && (dp[k1 + 1][j - 1] != (long long int)-1) && (gcdt[i][k1] > 1) && (gcdt[k1][j] > 1) && (gcdt[i][j] > 1)) // invalid: just have one point or cannot be pair
                {
                    pair = 1;
                    temp = (long long int)gcdt[i][k1] + (long long int)gcdt[k1][j] + dp[i + 1][k1 - 1] + dp[k1 + 1][j - 1];
                    if (temp > maxnum)
                        maxnum = temp;
                }
            }

            if (pair == 0)
            {
                // printf("(%d, %d) = -1\n", i, j);
                dp[i][j] = (long long int)-1;
            }
            else
            {
                dp[i][j] = maxnum;
                // printf("(%d, %d) = %d\n", i, j, maxnum);
            }
        }
    }

    printf("%lld", dp[0][N - 1]);
    return 0;
}