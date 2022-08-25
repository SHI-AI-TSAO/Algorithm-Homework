#include "ypglpk.hpp"
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
int N;
void Info(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X)
{
    printf("P: ");
    for (int i = 0; i < N; ++i)
    {
        if (P[i] == 1)
            printf("%d ", i);
    }
    printf("\n");
    printf("R: ");
    for (int i = 0; i < N; ++i)
    {
        if (R[i] == 1)
            printf("%d ", i);
    }
    printf("\n");
    printf("X: ");
    for (int i = 0; i < N; ++i)
    {
        if (X[i] == 1)
            printf("%d ", i);
    }
    printf("\n");
}
void Bron_Kerbosch(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X, std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &clique)
{
    if ((P[N] == 0) && (X[N] == 0)) // R is maximal clique
    {
        // printf("Clique!!\n");
        clique.push_back(std::vector<int>());
        for (int i = 0; i < N; ++i)
        {
            if (R[i] == 1)
                clique[clique.size() - 1].push_back(i); // maximal clique vector
        }
    }
    // choose a pivot in P&X
    // ???with the most neighbor in P
    int pivot = 0;
    int maxn = -1;
    for (int i = 0; i < N; ++i)
    {
        if ((P[i] == 1) && (maxn < graph[i][N]))
        {
            maxn = graph[i][N];
            pivot = i;
        }
        else if ((X[i] == 1) && (maxn < graph[i][N]))
        {
            maxn = graph[i][N];
            pivot = i;
        }
    }
    std::vector<std::vector<int>> Pc;
    std::vector<std::vector<int>> Rc;
    std::vector<std::vector<int>> Xc;
    for (int v = 0; v < N; ++v)
    {
        if ((P[v] == 1) && ((graph[v][pivot] == 0) || (v == pivot)))
        {
            // P' = P intersect neighbor(v)
            Pc.push_back(std::vector<int>());
            int count = 0;
            for (int j = 0; j < N; ++j)
            {
                if ((P[j] == 1) && ((graph[v][j] == 1) && (v != j)))
                {
                    Pc[Pc.size() - 1].push_back(1);
                    ++count;
                }
                else
                    Pc[Pc.size() - 1].push_back(0);
            }
            Pc[Pc.size() - 1].push_back(count);
            // R' = R union v
            Rc.push_back(std::vector<int>());
            for (int j = 0; j < (N + 1); ++j)
                Rc[Rc.size() - 1].push_back(R[j]);
            if (Rc[Rc.size() - 1][v] == 0)
            {
                Rc[Rc.size() - 1][v] = 1;
                Rc[Rc.size() - 1][N] += 1;
            }
            // X' = X intersect neighbor(v)
            Xc.push_back(std::vector<int>());
            count = 0;
            for (int j = 0; j < N; ++j)
            {
                if ((X[j] == 1) && ((graph[v][j] == 1) && (v != j)))
                {
                    Xc[Xc.size() - 1].push_back(1);
                    ++count;
                }
                else
                    Xc[Xc.size() - 1].push_back(0);
            }
            Xc[Xc.size() - 1].push_back(count);
            Bron_Kerbosch(Pc[Pc.size() - 1], Rc[Rc.size() - 1], Xc[Xc.size() - 1], graph, clique);
            P[v] = 0;
            P[N] -= 1;
            if (X[v] == 0)
            {
                X[v] = 1;
                X[N] += 1;
            }
        }
    }
}
int main()
{
    int n1, n2;
    int M, testcase;
    scanf("%d", &testcase);
    std::vector<std::vector<int>> Answer(testcase);
    for (int t = 0; t < testcase; ++t)
    {
        scanf("%d %d", &N, &M);
        std::vector<std::vector<int>> graph(N, std::vector<int>(N + 1, 0)); //+1 for # of neighbor
        std::vector<std::vector<int>> clique;
        std::vector<std::vector<int>> P;
        std::vector<std::vector<int>> R;
        std::vector<std::vector<int>> X;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N + 1; ++j)
            {
                if (i == j)
                    graph[i][j] = 1;
                else
                    graph[i][j] = 0;
            }
        }
        for (int i = 0; i < M; ++i)
        {
            scanf("%d %d", &n1, &n2);
            graph[n1][n2] = 1;
            graph[n2][n1] = 1;
            graph[n1][N] += 1;
            graph[n2][N] += 1;
        }
        R.push_back(std::vector<int>());
        for (int i = 0; i < (N + 1); ++i)
            R[0].push_back(0);
        P.push_back(std::vector<int>());
        for (int i = 0; i < N; ++i)
            P[0].push_back(1);
        P[0].push_back(N);
        X.push_back(std::vector<int>());
        for (int i = 0; i < (N + 1); ++i)
            X[0].push_back(0);
        Bron_Kerbosch(P[0], R[0], X[0], graph, clique);
        /*
        for (int c = 0; c < int(clique.size()); ++c)
        {
            for (int cc = 0; cc < int(clique[c].size()); ++cc)
                printf("%d ", clique[c][cc]);
            printf("\n");
        }
        */
        // LP
        std::vector<std::vector<double>> A(N + int(clique.size()), std::vector<double>(clique.size(), 0));
        std::vector<double> B(N + int(clique.size()));
        std::vector<double> contraint(int(clique.size()));
        std::vector<bool> isint(int(clique.size()), 1);
        // A
        for (int c = 0; c < int(clique.size()); ++c)
        {
            for (int cc = 0; cc < int(clique[c].size()); ++cc)
            {
                A[clique[c][cc]][c] = -1;
            }
        }

        for (int i = 0; i < int(clique.size()); ++i)
            A[N + i][i] = -1;

        // B
        for (int i = 0; i < N; ++i)
            B[i] = -1;
        for (int i = N; i < N + int(clique.size()); ++i)
            B[i] = 0;
        // C
        for (int i = 0; i < int(clique.size()); ++i)
            contraint[i] = -1;
        std::pair<double, std::vector<double>> res = ypglpk::linear_programming(A, B, contraint);
        res = ypglpk::mixed_integer_linear_programming(A, B, contraint, isint);
        // output result
        std::vector<bool> inset(N, 0);
        std::vector<int> temp;
        // printf("Min: %d\n", int(-res.first));
        Answer[t].push_back(int(-res.first));
        Answer[t].push_back(-1);
        int first = 1;
        for (int i = 0; i < int(clique.size()); ++i)
        {
            if (res.second[i] > 0) // choosen
            {
                for (int cc = 0; cc < int(clique[i].size()); ++cc)
                {
                    if (inset[clique[i][cc]] == 0)
                    {
                        temp.push_back(clique[i][cc]);
                        inset[clique[i][cc]] = 1;
                    }
                }
                if (first == 1)
                {
                    // printf("%ld", temp.size());
                    Answer[t].push_back(temp.size());
                    first = 0;
                }
                else
                {
                    // printf("\n%ld", temp.size());
                    Answer[t].push_back(-1);
                    Answer[t].push_back(temp.size());
                }
                while (!temp.empty())
                {
                    // printf(" %d", temp.back());
                    Answer[t].push_back(-2);
                    Answer[t].push_back(temp.back());
                    temp.pop_back();
                }
            }
        }
        if (t != (testcase - 1))
            Answer[t].push_back(-1);
    }

    for (int t = 0; t < testcase; ++t)
    {
        for (int i = 0; i < int(Answer[t].size()); ++i)
        {
            if (Answer[t][i] == -2)
                printf(" ");
            else if (Answer[t][i] == -1)
                printf("\n");
            else
                printf("%d", Answer[t][i]);
        }
    }
}