#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>
#include <tuple>
int P_N(int *a, int *pre, int *next, int N)
{
    int positive = -1;
    int negative = -1 << 31;
    int pn, idxp = -1, idxn = -1, root = -1;
    if (a[0] > 0)
    {
        pn = 1;
        positive = a[0];
        idxp = 0;
    }
    else
    {
        pn = -1;
        negative = a[0];
        idxn = 0;
    }
    for (int i = 1; i < (N - 1); ++i)
    {
        if (a[i] > 0)
        {
            if (pn == -1) // change sign
            {
                if (idxp >= 0) // P N done
                {
                    if (root == -1)
                        root = idxp;
                    next[idxp] = idxn;
                    pre[idxn] = idxp;
                }
                positive = a[i];
                idxp = i;
                pn = 1;
            }
            else
            {
                if (a[i] > positive)
                {
                    positive = a[i];
                    idxp = i;
                }
            }
        }
        else
        {
            if (pn == 1) // change sign
            {
                if (idxn >= 0) // N P done
                {
                    if (root == -1)
                        root = idxn;
                    next[idxn] = idxp;
                    pre[idxp] = idxn;
                }
                pn = -1;
                negative = a[i];
                idxn = i;
            }
            else
            {
                if (a[i] > negative)
                {
                    negative = a[i];
                    idxn = i;
                }
            }
        }
    }

    if (a[N - 1] > 0)
    {
        if (pn == -1) // idxn must exist
        {
            if ((root == -1) && (idxp >= 0)) // P N
                root = idxp;
            else if (root == -1) // N
                root = idxn;
            if (idxp >= 0) // P N
            {
                next[idxp] = idxn;
                pre[idxn] = idxp;
            }
            next[idxn] = N - 1;
            pre[N - 1] = idxn;
            next[N - 1] = -1; // end of list
            pre[root] = N - 1;
        }
        else if (a[N - 1] > positive)
        {
            if ((root == -1) && (idxn >= 0)) // N P
                root = idxn;
            else if (root == -1) // P
                root = N - 1;
            if (idxn >= 0)
            {
                next[idxn] = N - 1;
                pre[N - 1] = idxn;
            }
            next[N - 1] = -1; // end of list
            pre[root] = N - 1;
        }
        else
        {
            if ((root == -1) && (idxn >= 0)) // N P
                root = idxn;
            else if (root == -1) // P
                root = idxp;
            if (idxn >= 0)
            {
                next[idxn] = idxp;
                pre[idxp] = idxn;
            }
            next[idxp] = -1; // end of list
            pre[root] = idxp;
        }
    }
    else
    {
        if (pn == 1) // idxp must exist
        {
            if ((root == -1) && (idxn >= 0)) // N P
                root = idxn;
            else if (root == -1) // P
                root = idxp;
            if (idxn >= 0) // N P
            {
                next[idxn] = idxp;
                pre[idxp] = idxn;
            }
            next[idxp] = N - 1;
            pre[N - 1] = idxp;
            next[N - 1] = -1; // end of list
            pre[root] = N - 1;
        }
        else if (a[N - 1] > negative)
        {
            if ((root == -1) && (idxp >= 0)) // P N
                root = idxp;
            else if (root == -1) // N
                root = N - 1;
            if (idxp >= 0)
            {
                next[idxp] = N - 1;
                pre[N - 1] = idxp;
            }
            next[N - 1] = -1; // end of list
            pre[root] = N - 1;
        }
        else
        {
            if ((root == -1) && (idxp >= 0)) // P N
                root = idxp;
            else if (root == -1) // N
                root = idxn;
            if (idxp >= 0)
            {
                next[idxp] = idxn;
                pre[idxn] = idxp;
            }
            next[idxn] = -1; // end of list
            pre[root] = idxn;
        }
    }
    return root;
}
int Pair(int *a, int *pre, int *next, int root, int *pair, int *paid, int *papoint)
{
    int idx = root;
    int p1 = 0;
    while (1)
    {
        pair[p1] = a[idx];
        paid[p1] = p1;
        papoint[p1] = idx;
        idx = next[idx];
        if (idx != -1)
        {
            pair[p1] += a[idx];
            p1 += 1;
        }
        else
            return (p1 - 1);
    }
    return (p1 - 1);
}
void Compare(int *z, int *index, int *index2, int start, int mid, int last)
{
    // printf("compare\n");
    int *ztemp = (int *)malloc((last - start + (int)1) * sizeof(int));
    int *idtemp = (int *)malloc((last - start + (int)1) * sizeof(int));
    int *idtemp2 = (int *)malloc((last - start + (int)1) * sizeof(int));
    int pt1 = start;
    int pt2 = mid + 1;
    int temp_index = 0;

    while (1)
    {
        if (z[pt1] <= z[pt2])
        {
            ztemp[temp_index] = z[pt1];
            idtemp[temp_index] = index[pt1];
            idtemp2[temp_index] = index2[pt1];
            pt1 += 1;
        }
        else
        {
            ztemp[temp_index] = z[pt2];
            idtemp[temp_index] = index[pt2];
            idtemp2[temp_index] = index2[pt2];
            pt2 += 1;
        }
        temp_index += 1;

        if (pt1 > mid)
        {
            while (pt2 <= last)
            {
                ztemp[temp_index] = z[pt2];
                idtemp[temp_index] = index[pt2];
                idtemp2[temp_index] = index2[pt2];
                pt2 += 1;
                temp_index += 1;
            }
            break;
        }
        else if (pt2 > last)
        {
            while (pt1 <= mid)
            {
                ztemp[temp_index] = z[pt1];
                idtemp[temp_index] = index[pt1];
                idtemp2[temp_index] = index2[pt1];
                pt1 += 1;
                temp_index += 1;
            }
            break;
        }
    }

    for (int i = start; i <= last; ++i)
    {
        z[i] = ztemp[i - start];
        index[i] = idtemp[i - start];
        index2[i] = idtemp2[i - start];
    }
    free(ztemp);
    free(idtemp);
    free(idtemp2);
    return;
}
void Merge(int *z, int *index, int *index2, int start, int last)
{
    if (start >= last)
        return;
    int mid = (start + last) / 2;
    Merge(z, index, index2, start, mid);
    Merge(z, index, index2, mid + 1, last);
    Compare(z, index, index2, start, mid, last);
    return;
}
void DP(int *a, int root, int *pair, int *paid, int *papoint, int pair_num, long long int *dp, int N, int *pre, int *next, int flag)
{
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> minqueue; //, std::greater<std::pair<int, std::pair<int, int>>>
    for (int i = 0; i <= pair_num; ++i)
        minqueue.push(std::make_tuple(pair[i], papoint[i], next[papoint[i]]));

    int *del = (int *)malloc((N) * sizeof(int));
    for (int i = 0; i < N; ++i)
        del[i] = 0;

    int first = root;
    int last = pre[root];
    int i;
    for (i = (N - 1); i >= 0; --i)
    {
        //  number must contain > pair number + 1
        if ((i + 1) > (pair_num + 2))
            dp[i] = 0;
        else if ((i + 1) == (pair_num + 2))
        {
            dp[i] = 0;
            int idx = root;
            while (idx != -1)
            {
                dp[i] += (long long int)a[idx];
                idx = next[idx];
            }
            // printf("dp[%d]=%d\n", i, dp[i]);
            break;
        }
    }

    if (flag == 1)
    {
        if ((i - 1) >= 0)
        {
            if (a[first] < a[last])
            {
                dp[i - 1] = dp[i] - (long long int)a[first];
                del[first] = 1;
                first = next[first];
            }
            else
            {
                dp[i - 1] = dp[i] - (long long int)a[last];
                del[last] = 1;
                last = pre[last];
            }
        }
        i--;
    }

    for (i = i - 2; i >= 0; i = i - 2)
    {

        while (1) // find avalible minpair
        {
            // printf("%d %d %d\n", minpair, papoint[minpair], next_t[papoint[minpair]]);
            if (minqueue.empty()) // no more pair
                break;
            else if ((del[std::get<1>(minqueue.top())] == 1) || (del[std::get<2>(minqueue.top())] == 1)) // one of element of minpair is delete
            {
                // printf("pop:%d, del1:%d, del2:%d\n", std::get<0>(minqueue.top()), std::get<1>(minqueue.top()), std::get<2>(minqueue.top()));
                minqueue.pop();
            }
            else
                break;
        }

        if (!minqueue.empty()) // have pair
        {
            int minpairnum = std::get<0>(minqueue.top());
            // printf("(head, tail, minpair) = (%d, %d, %d)\n", first, last, minpairnum);
            if (minpairnum < (a[first] + a[last])) // dp[i+2] - min pair
            {
                int first_element = std::get<1>(minqueue.top());
                // printf("min pair: %d\n", pair[minpair]);
                dp[i] = dp[i + 2] - (long long int)minpairnum;
                minqueue.pop();
                // printf("pop: %d\n", minpairnum);
                //   delete pair element
                del[first_element] = 1;
                del[next[first_element]] = 1;

                if ((first_element != first) && (next[first_element] != last)) // a and b exist
                {
                    next[pre[first_element]] = next[next[first_element]]; // a -> x x -> b ---- a -> b
                    pre[next[next[first_element]]] = pre[first_element];  // a <- x x <- b ---- a <- b
                                                                          // new pair (a,b)
                    minqueue.push(std::make_tuple(a[pre[first_element]] + a[next[next[first_element]]], pre[first_element], next[pre[first_element]]));
                    // printf("push: %d, mintop: %d\n", a[pre[first_element]] + a[next[next[first_element]]], minqueue.top().first);
                }

                // if head and tail deleted
                if (first == first_element)
                    first = next[next[first_element]];
                if (last == next[first_element])
                    last = pre[first_element];
                // for (int k = 0; k < N; ++k)
                //     printf("%d ", del[k]);
                // printf("\n");
                //  printf("dp[%d]=%d\n", i, dp[i]);
            }
            else // dp[i+2] - head & tail
            {
                // printf("head tail: %d\n", (a[first] + a[last]));
                dp[i] = dp[i + 2] - (long long int)a[first] - (long long int)a[last];
                // printf("first,last: %d\n", a[first] + a[last]);
                del[first] = 1;
                del[last] = 1;
                first = next[first];
                last = pre[last];
                // printf("dp[%d]=%d\n", i, dp[i]);
            }
        }
        else
        {
            // printf("head tail: %d\n", (a[first] + a[last]));
            dp[i] = dp[i + 2] - (long long int)a[first] - (long long int)a[last];
            // printf("first,last: %d\n", a[first] + a[last]);
            del[first] = 1;
            del[last] = 1;
            first = next[first];
            last = pre[last];
            // printf("dp[%d]=%d\n", i, dp[i]);
        }
    }
    free(del);
    return;
}
int main()
{
    int testnum;
    int flag;
    scanf("%d %d", &testnum, &flag);
    long long int *it[testnum];
    int ansnum[testnum];
    for (int test = 0; test < testnum; ++test)
    {
        int N;
        scanf("%d", &N);
        ansnum[test] = N;
        int *a = (int *)malloc((N) * sizeof(int));
        int *pre = (int *)malloc((N) * sizeof(int));
        int *next = (int *)malloc((N) * sizeof(int));
        long long int *dp = (long long int *)malloc((N) * sizeof(long long int));
        // for (int i = 0; i < N; ++i)
        //     dp[i] = -1 << 31;
        for (int i = 0; i < (N - 1); ++i)
            scanf("%d ", &a[i]);
        scanf("%d", &a[N - 1]);
        // deal with PNPNPN.....
        int idx = P_N(a, pre, next, N);
        /*
        int ii = idx;
        while (ii != -1)
        {
            printf("%d(%d,%d) ", a[ii], pre[ii], next[ii]);
            ii = next[ii];
        }
        printf("\n");
        */
        int *pair = (int *)malloc((N) * sizeof(int));
        int *paid = (int *)malloc((N) * sizeof(int));
        int *papoint = (int *)malloc((N) * sizeof(int));
        // find pair
        int pair_num = Pair(a, pre, next, idx, pair, paid, papoint);
        // sort
        if (pair_num > 0)
            Merge(pair, paid, papoint, 0, pair_num); // redundant
        // for (int i = 0; i <= pair_num; ++i)
        //     printf("%d(%d) ", pair[i], papoint[i]);
        DP(a, idx, pair, paid, papoint, pair_num, dp, N, pre, next, 0);
        idx = P_N(a, pre, next, N);
        DP(a, idx, pair, paid, papoint, pair_num, dp, N, pre, next, 1);
        it[test] = dp;
        free(a);
        free(pre);
        free(next);
        free(pair);
        free(paid);
        free(papoint);
    }
    for (int j = 0; j < testnum; ++j) // output dp answer
    {
        for (int i = 0; i < (ansnum[j] - 1); ++i)
            printf("%lld ", *(it[j] + i));
        printf("%lld", *(it[j] + ansnum[j] - 1));
        if (j < (testnum - 1))
            printf("\n");
    }
    return 0;
}