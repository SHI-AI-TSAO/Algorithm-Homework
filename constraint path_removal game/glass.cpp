#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <tuple>
#include <stack>
using namespace std;

struct Node
{
    int i = 0;
    int j = 0;
    int isroot = -1;
    struct Node *parent;
};
struct Node *Newnode(int n, int m)
{
    struct Node *temp;
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->parent = NULL;
    temp->i = n;
    temp->j = m;
    temp->isroot = 0;
    return temp;
}
/*
void DP(vector<vector<long long int>> &a, vector<vector<vector<long long int>>> &dp, int N, int M, int K, Node (*step)[10][10]) //, struct Node *node
{
    long long int maxnum = 0;
    for (int n = 0; n < N; n++)
    {
        for (int m = 0; m < M; m++)
        {
            maxnum = -1LL << 63;
            step[n][m][0] = Newnode(n, m);
            for (int d = 1; d <= K; ++d)
            {
                step[n][m][d] = Newnode(n, m);
                if (((n - 1) < 0) && ((m - 1) < 0))
                    break;
                else if ((n - 1) < 0)
                {
                    if (((m - 1) >= 0) && (dp[n][m - 1][d - 1] > -1LL << 63))
                    {
                        dp[n][m][d] = dp[n][m - 1][d - 1];
                        step[n][m][d]->parent = step[n][m - 1][d - 1]->parent;
                        if (dp[n][m][d] > maxnum)
                        {
                            maxnum = dp[n][m][d];
                            step[n][m][0]->parent = step[n][m][d]->parent;
                        }
                    }
                }
                else if ((m - 1) < 0)
                {
                    if (((n - 1) >= 0) && (dp[n - 1][m][d - 1] > -1LL << 63))
                    {
                        dp[n][m][d] = dp[n - 1][m][d - 1];
                        step[n][m][d]->parent = step[n - 1][m][d - 1]->parent;
                        if (dp[n][m][d] > maxnum)
                        {
                            maxnum = dp[n][m][d];
                            step[n][m][0]->parent = step[n][m][d]->parent;
                        }
                    }
                }
                else if (dp[n][m - 1][d - 1] > dp[n - 1][m][d - 1])
                {
                    dp[n][m][d] = dp[n][m - 1][d - 1];
                    step[n][m][d]->parent = step[n][m - 1][d - 1]->parent;
                    if (dp[n][m][d] > maxnum)
                    {
                        maxnum = dp[n][m][d];
                        step[n][m][0]->parent = step[n][m][d]->parent;
                    }
                }
                else if (dp[n - 1][m][d - 1] > -1LL << 63)
                {
                    dp[n][m][d] = dp[n - 1][m][d - 1];
                    step[n][m][d]->parent = step[n - 1][m][d - 1]->parent;
                    if (dp[n][m][d] > maxnum)
                    {
                        maxnum = dp[n][m][d];
                        step[n][m][0]->parent = step[n][m][d]->parent;
                    }
                }
                printf("(%d, %d, %d) = %lld, from point: (%d, %d)\n", n, m, d, dp[n][m][d], step[n][m][d]->parent->i, step[n][m][d]->parent->j);
            }

            if ((maxnum > -1LL << 63) && (a[n][m] > -1LL << 63))
            {
                // dp[n][m][K + 1] = maxnum + a[n][m]; // max num for (n,m)
                dp[n][m][0] = maxnum + a[n][m]; // max num for (n,m)
                printf("find max:(%d, %d) = %lld\n", n, m, dp[n][m][0]);
            }
            else if ((n > 0) || (m > 0))
            {
                dp[n][m][0] = -1LL << 63;
                printf("find max:(%d, %d) = %lld\n", n, m, dp[n][m][0]);
            }
        }
    }
}
*/
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int testnum;
    cin >> testnum;
    long long int ans[testnum];
    stack<pair<int, int>> pairstack[testnum];
    for (int t = 0; t < testnum; ++t)
    {
        int N, M, K;
        string emptyline;
        getline(cin, emptyline);
        cin >> N >> M >> K;
        vector<vector<long long int>> a(N, vector<long long int>(M, 0));
        // dp store: have already walk k step, the max num it has earned.
        vector<vector<vector<long long int>>> dp(N, vector<vector<long long int>>(M, vector<long long int>(K + 1, -1LL << 63)));
        //(self index, parent index)
        vector<vector<vector<pair<int, int>>>> step(N, vector<vector<pair<int, int>>>(M, vector<pair<int, int>>(K + 1)));
        vector<vector<pair<int, int>>> step0(N, vector<pair<int, int>>(M));
        // tuple<int, int, int, int> step0[N][M];
        cin.get(); // clear a '\n'
        for (int n = 0; n < N; ++n)
        {
            int m = 0;
            while (cin.peek() != '\n')
            {
                if (cin.peek() == ' ')
                    cin.get(); // clear a space
                else if (cin.peek() == 'X')
                {
                    cin.get();
                    a[n][m] = -1LL << 63;
                    m += 1;
                }
                else
                {
                    cin >> a[n][m];
                    m += 1;
                }
            }
            cin.get(); // clear a '\n'
        }
        /*
        for (int n = 0; n < N; ++n)
        {
            for (int m = 0; m < M; ++m)
                cout << a[n][m] << " ";
            cout << endl;
        }
        */

        for (int n = 0; n < N; ++n)
            for (int m = 0; m < M; ++m)
                dp[n][m][0] = a[n][m];
        /*
        for (int n = 0; n < N; ++n)
            for (int m = 0; m < M; ++m)
                step[n][m][0] = Newnode(n, m);
        step[0][0][0]->isroot = 1;
        step[0][0][0]->parent = step[0][0][0];
        */
        step0[0][0] = make_pair(0, 0);
        step[0][0][0] = step0[0][0];

        // DP(a, dp, N, M, K, step);
        int iidx = 0;
        int jidx = 0;
        long long int maxnum = 0;
        for (int n = 0; n < N; n++)
        {
            for (int m = 0; m < M; m++)
            {
                maxnum = -1LL << 63;
                for (int d = 1; d <= K; ++d)
                {
                    // step[n][m][d] = Newnode(n, m);
                    if (((n - 1) < 0) && ((m - 1) < 0))
                        break;
                    else if ((n - 1) < 0)
                    {
                        if (((m - 1) >= 0) && (dp[n][m - 1][d - 1] > -1LL << 63))
                        {
                            dp[n][m][d] = dp[n][m - 1][d - 1];
                            if ((d - 1) == 0)
                            {
                                step[n][m][d] = make_pair(n, m - 1);
                                // step[n][m][d]->parent = step[n][m - 1][d - 1];
                            }
                            else
                            {
                                iidx = step[n][m - 1][d - 1].first;
                                jidx = step[n][m - 1][d - 1].second;
                                step[n][m][d] = make_pair(iidx, jidx);
                                // step[n][m][d]->parent = step[n][m - 1][d - 1]->parent;
                            }

                            if (dp[n][m][d] > maxnum)
                            {
                                maxnum = dp[n][m][d];
                                iidx = step[n][m][d].first;
                                jidx = step[n][m][d].second;
                                step[n][m][0] = make_pair(iidx, jidx);
                                step0[n][m] = step[n][m][0];
                                // step[n][m][0]->parent = step[n][m][d]->parent;
                            }
                        }
                    }
                    else if ((m - 1) < 0)
                    {
                        if (((n - 1) >= 0) && (dp[n - 1][m][d - 1] > -1LL << 63))
                        {
                            dp[n][m][d] = dp[n - 1][m][d - 1];

                            if ((d - 1) == 0)
                            {
                                step[n][m][d] = make_pair(n - 1, m);
                                // step[n][m][d]->parent = step[n - 1][m][d - 1];
                            }
                            else
                            {
                                iidx = step[n - 1][m][d - 1].first;
                                jidx = step[n - 1][m][d - 1].second;
                                step[n][m][d] = make_pair(iidx, jidx);
                                // step[n][m][d]->parent = step[n - 1][m][d - 1]->parent;
                            }

                            if (dp[n][m][d] > maxnum)
                            {
                                maxnum = dp[n][m][d];
                                iidx = step[n][m][d].first;
                                jidx = step[n][m][d].second;
                                step[n][m][0] = make_pair(iidx, jidx);
                                step0[n][m] = step[n][m][0];
                                // step[n][m][0]->parent = step[n][m][d]->parent;
                            }
                        }
                    }
                    else if (dp[n][m - 1][d - 1] > dp[n - 1][m][d - 1])
                    {
                        dp[n][m][d] = dp[n][m - 1][d - 1];
                        if ((d - 1) == 0)
                        {
                            step[n][m][d] = make_pair(n, m - 1);
                            // step[n][m][d]->parent = step[n][m - 1][d - 1];
                        }
                        else
                        {
                            iidx = step[n][m - 1][d - 1].first;
                            jidx = step[n][m - 1][d - 1].second;
                            step[n][m][d] = make_pair(iidx, jidx);
                            // step[n][m][d]->parent = step[n][m - 1][d - 1]->parent;
                        }
                        if (dp[n][m][d] > maxnum)
                        {
                            maxnum = dp[n][m][d];
                            iidx = step[n][m][d].first;
                            jidx = step[n][m][d].second;
                            step[n][m][0] = make_pair(iidx, jidx);
                            step0[n][m] = step[n][m][0];
                            // step[n][m][0]->parent = step[n][m][d]->parent;
                        }
                    }
                    else if (dp[n - 1][m][d - 1] > -1LL << 63)
                    {
                        dp[n][m][d] = dp[n - 1][m][d - 1];

                        if ((d - 1) == 0)
                        {
                            step[n][m][d] = make_pair(n - 1, m);
                            // step[n][m][d]->parent = step[n - 1][m][d - 1];
                        }
                        else
                        {
                            iidx = step[n - 1][m][d - 1].first;
                            jidx = step[n - 1][m][d - 1].second;
                            step[n][m][d] = make_pair(iidx, jidx);
                            // step[n][m][d]->parent = step[n - 1][m][d - 1]->parent;
                        }

                        if (dp[n][m][d] > maxnum)
                        {
                            maxnum = dp[n][m][d];
                            iidx = step[n][m][d].first;
                            jidx = step[n][m][d].second;
                            step[n][m][0] = make_pair(iidx, jidx);
                            step0[n][m] = step[n][m][0];
                            // step[n][m][0]->parent = step[n][m][d]->parent;
                        }
                    }
                    /*
                    if (step[n][m][d]->parent != NULL)
                        printf("(%d, %d, %d) = %lld, from point: (%d, %d)\n", n, m, d, dp[n][m][d], step[n][m][d]->parent->i, step[n][m][d]->parent->j);
                    else
                        printf("(%d, %d, %d) = %lld, from point: NULL\n", n, m, d, dp[n][m][d]);
                    */
                }
                // free the front glass

                // if ((n - 1) >= 0)
                //{
                //  for (int kk = 1; kk <= K; ++kk)
                //      free(step[n - 1][m][kk]);
                //  vector<long long int>().swap(dp[n - 1][m]);
                // vector<pair<int, int>>().swap(step[n - 1][m]);
                //}

                if ((maxnum > -1LL << 63) && (a[n][m] > -1LL << 63))
                {
                    dp[n][m][0] = maxnum + a[n][m]; // max num for (n,m)
                    // printf("find max:(%d, %d) = %lld, from point: (%d, %d)\n", n, m, dp[n][m][0], step0[n][m].first, step0[n][m].second);
                }
                else if ((n > 0) || (m > 0))
                {
                    dp[n][m][0] = -1LL << 63;
                    // printf("find max:(%d, %d) = %lld\n", n, m, dp[n][m][0]);
                }
            }
        }
        ans[t] = dp[N - 1][M - 1][0];
        pair<int, int> tmp;
        if (ans[t] > -1LL << 63)
        {
            tmp = make_pair(N - 1, M - 1);
            while (1)
            {
                iidx = tmp.first;
                jidx = tmp.second;
                pairstack[t].push(make_pair(iidx + 1, jidx + 1));
                if ((iidx == 0) && (jidx == 0))
                    break;
                tmp = step0[iidx][jidx];
            }
        }

        for (int i = 0; i < a.size(); ++i)
            vector<long long int>().swap(a[i]);
        /*
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                vector<long long int>().swap(dp[i][j]);
        */
        /*
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                for (int k = 0; k < (K + 1); ++k)
                    free(step[i][j][k]);
        */
    }

    for (int t = 0; t < testnum; ++t)
    {
        if (ans[t] > -1LL << 63)
        {
            printf("Passable\n%lld\n", ans[t]);
            int size = pairstack[t].size();
            printf("%d\n", size);
            for (int j = 0; j < size; ++j)
            {
                if ((t == (testnum - 1)) && (j == (size - 1)))
                    printf("%d %d", (pairstack[t].top()).first, (pairstack[t].top()).second);
                else
                    printf("%d %d\n", (pairstack[t].top()).first, (pairstack[t].top()).second);

                pairstack[t].pop();
            }
        }
        else
        {
            if (t != (testnum - 1))
                printf("Impassable\n");
            else
                printf("Impassable");
        }
    }

    return 0;
}