#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
int N, M;
int begin_i;
int end_i;
int64_t minimum = std::numeric_limits<int64_t>::max();
int64_t RiskValue2(int cut, std::vector<int64_t> &a)
{
    int64_t temp = 0;
    if (cut == 0)
        temp = std::abs(a[cut] - a[N - 1]) * (-1);
    else
        temp = std::abs(a[cut] - a[cut - 1]) * (-1);
    return temp;
}
int64_t RiskValue3(int pre, int cut, std::vector<int64_t> &a)
{
    int64_t temp = 0;
    if (N >= 3)
    {
        if (cut == 0)
        {
            if ((N - 1 != begin_i) && (N - 1 != pre))
                temp += a[N - 1] * ((a[N - 2] & a[N - 1]) ^ (a[N - 1] | a[cut]) ^ (a[N - 2] + a[cut]));
            if (cut != end_i)
                temp += a[cut] * ((a[N - 1] & a[cut]) ^ (a[cut] | a[cut + 1]) ^ (a[N - 1] + a[cut + 1]));
        }
        else if (cut == 1)
        {
            if ((cut - 1 != begin_i) && (cut - 1 != pre))
                temp += a[cut - 1] * ((a[N - 1] & a[cut - 1]) ^ (a[cut - 1] | a[cut]) ^ (a[N - 1] + a[cut]));
            if (cut != end_i)
                temp += a[1] * ((a[0] & a[1]) ^ (a[1] | a[2]) ^ (a[0] + a[2]));
        }
        else if (cut == N - 1)
        {
            if ((cut - 1 != begin_i) && (cut - 1 != pre))
                temp += a[cut - 1] * ((a[cut - 2] & a[cut - 1]) ^ (a[cut - 1] | a[cut]) ^ (a[cut - 2] + a[cut]));
            if (cut != end_i)
                temp += a[cut] * ((a[cut - 1] & a[cut]) ^ (a[cut] | a[0]) ^ (a[cut - 1] + a[0]));
        }
        else
        {
            if ((cut - 1 != begin_i) && (cut - 1 != pre))
                temp = a[cut - 1] * ((a[cut - 2] & a[cut - 1]) ^ (a[cut - 1] | a[cut]) ^ (a[cut - 2] + a[cut]));

            if (cut != end_i)
                temp += a[cut] * ((a[cut - 1] & a[cut]) ^ (a[cut] | a[cut + 1]) ^ (a[cut - 1] + a[cut + 1]));
        }
    }
    return temp;
}
int64_t RiskValue(int start, int end, std::vector<int64_t> &b)
{
    int64_t value = 0;
    if (start > end)
    {
        std::vector<int64_t> temp;
        for (int i = start; i < N; ++i)
            temp.push_back(b[i]);
        for (int i = 0; i <= end; ++i)
            temp.push_back(b[i]);

        for (int i = 0; i < temp.size(); ++i)
            value += temp[i];
        for (int i = 1; i < temp.size(); ++i)
            value -= std::abs(temp[i] - temp[i - 1]);
        for (int i = 2; i < temp.size(); ++i)
            value += temp[i - 1] * ((temp[i - 2] & temp[i - 1]) ^ (temp[i - 1] | temp[i]) ^ (temp[i - 2] + temp[i]));
    }
    else
    {
        for (int i = start; i <= end; ++i)
            value += b[i];
        for (int i = start + 1; i <= end; ++i)
            value -= std::abs(b[i] - b[i - 1]);
        for (int i = start + 2; i <= end; ++i)
            value += b[i - 1] * ((b[i - 2] & b[i - 1]) ^ (b[i - 1] | b[i]) ^ (b[i - 2] + b[i]));
    }
    return value;
}
int main()
{
    scanf("%d %d", &N, &M);
    std::vector<int64_t> a(N), tt(N);
    std::vector<std::vector<int64_t>> cut(N, std::vector<int64_t>(M, std::numeric_limits<int64_t>::max()));
    std::vector<std::vector<std::pair<int64_t, int>>> ncut(N, std::vector<std::pair<int64_t, int>>(M, std::make_pair(std::numeric_limits<int64_t>::max(), -1)));
    for (int i = 0; i < N; ++i)
    {
        if (i == N - 1)
            scanf("%lld", &a[i]);
        else
            scanf("%lld ", &a[i]);
    }
    // printf("%lld\n", RiskValue(1, 0, a));
    // printf("%lld %lld\n", RiskValue(1, 1, a), RiskValue(2, 0, a));
    // printf("%lld %lld %lld\n", RiskValue(1, 1, a), RiskValue(2, 3, a), RiskValue(4, 0, a));
    srand(7777);
    int found[N];
    for (int i = 0; i < N; ++i)
        found[i] = 0;
    int coefficient = 3;
    /*
    if ((0 < N) && (N < 10))
        coefficient = 0;
    else if ((10 <= N) && (N < 250))
        coefficient = 10;
    else if ((250 <= N) && (N < 500))
        coefficient = 5;
    else // if (500 <= N <= 1000)
        coefficient = 2;
        */
    if (M * N <= 250000)
        coefficient = 5;
    else if (M * N <= 500000)
        coefficient = 3;
    else
        coefficient = 2;
    for (int c = 0; c < (int(coefficient * N / M) + 20); ++c)
    {
        if (c >= N)
            continue;
        int x = rand() % N;
        while (found[x] == 1)
            x = rand() % N;
        // printf("%d ", x);
        found[x] = 1;
        int first = 0;
        int idx = -1;
        for (int i = x; i < N; ++i)
            tt[++idx] = a[i];
        for (int i = 0; i < x; ++i)
            tt[++idx] = a[i];
        for (int i = 0; i < N; ++i)
            a[i] = tt[i];
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                cut[i][j] = std::numeric_limits<int64_t>::max();
                ncut[i][j].first = std::numeric_limits<int64_t>::max();
                ncut[i][j].second = -1;
            }
        }
        // printf("\nfirst cut on: %d\n", first);
        //  N-1, N-2, N-M -> M
        //   Total Risk
        int64_t total_risk;
        if (first == 0)
        {
            total_risk = RiskValue(first, N - 1, a);
            begin_i = 0;
            end_i = N - 1;
        }
        else
        {
            begin_i = first;
            end_i = first - 1;
            total_risk = RiskValue(first, first - 1, a);
        }
        // printf("Total risk: %lld\n", total_risk);

        int64_t tmp1, tmp2;
        for (int m = 0; m < M; ++m)
        {
            for (int n = m; n < N; ++n)
            {
                if (m == 0)
                {
                    if (n == first)
                        cut[n][m] = total_risk;
                    if (n > first)
                    {
                        ncut[n][m].first = total_risk;
                        ncut[n][m].second = first;
                    }
                }
                else
                {
                    // cut on n
                    if (cut[n - 1][m - 1] < std::numeric_limits<int64_t>::max())
                        tmp1 = cut[n - 1][m - 1] - RiskValue2(n, a) - RiskValue3(n - 1, n, a);
                    else
                        tmp1 = std::numeric_limits<int64_t>::max();
                    if (ncut[n - 1][m - 1].first < std::numeric_limits<int64_t>::max())
                        tmp2 = ncut[n - 1][m - 1].first - RiskValue2(n, a) - RiskValue3(ncut[n - 1][m - 1].second, n, a);
                    else
                        tmp2 = std::numeric_limits<int64_t>::max();

                    if (tmp1 < tmp2)
                        cut[n][m] = tmp1;
                    else
                        cut[n][m] = tmp2;
                    // not cut on n

                    tmp1 = cut[n - 1][m];
                    tmp2 = ncut[n - 1][m].first;
                    if (tmp1 < tmp2)
                    {
                        ncut[n][m].first = tmp1;
                        ncut[n][m].second = n - 1;
                    }
                    else
                    {
                        ncut[n][m].first = tmp2;
                        ncut[n][m].second = ncut[n - 1][m].second;
                    }
                }
                // printf("(n, m)=(%d, %d) = %lld, %lld\n", n, m, cut[n][m], ncut[n][m].first);
            }
        }
        if (ncut[N - 1][M - 1].first < minimum)
            minimum = ncut[N - 1][M - 1].first;
        if (cut[N - 1][M - 1] < minimum)
            minimum = cut[N - 1][M - 1];
    }
    printf("%lld", minimum);
    return 0;
}