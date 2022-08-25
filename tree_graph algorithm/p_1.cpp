#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
int time;
void DFS_visit(std::vector<std::vector<int>> &graph, int u, int *color, std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>> &finish, int *v1)
{
    time += 1;
    for (int i = 0; i < graph[u].size(); ++i)
    {
        if (color[graph[u][i]] == 1)
        {
            color[graph[u][i]] = 0;
            // printf(" %d", graph[u][i]);
            DFS_visit(graph, graph[u][i], color, finish, v1);
        }
    }
    time += 1;
    finish.push(std::make_pair(time, u));
    v1[u] = 1;
}
void DFS(std::vector<std::vector<int>> &graph, int u, int N, std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>> &finish, int *visit, int *v1)
{
    int color[N + 1];
    time = 0;
    for (int i = 0; i < (N + 1); ++i)
    {
        v1[i] = 0;
        if (visit[i] == 1)
            color[i] = 0;
        else
            color[i] = 1; // avialible
    }
    color[u] = 0;
    // printf("%d", u);
    DFS_visit(graph, u, color, finish, v1);
}
int Different(int *weak, int u, int v)
{
    while (weak[u] != -1)
        u = weak[u];
    while (weak[v] != -1)
        v = weak[v];
    if (u == v)
        return -1;
    else
        return 1;
}
int Connect(std::vector<std::vector<int>> &new_graph, int u, int v)
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>> finish;
    int visit[new_graph.size() + 1], v1[new_graph.size() + 1];
    for (int i = 0; i < (new_graph.size() + 1); ++i)
        visit[i] = 0;
    DFS(new_graph, u, new_graph.size(), finish, visit, v1);
    if (v1[v] == 1)
        return 1;
    else
        return -1;
}
void DAG(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &graph_D, std::vector<std::vector<int>> &scc, int *group, std::vector<std::pair<int, int>> &new_edge)
{
    if (scc.size() == 1)
        return;
    else
    {
        int in[scc.size()], out[scc.size()], visit[scc.size() + 1], connectto;
        std::vector<std::vector<int>> new_graph;
        for (int i = 0; i < scc.size(); ++i)
        {
            in[i] = 0;
            out[i] = 0;
            visit[i] = 0;
            new_graph.push_back(std::vector<int>());
        }
        // Graph to DAG graph
        for (int i = 0; i < scc.size(); ++i)
        {
            for (int j = 0; j < scc[i].size(); ++j)
            {
                for (int k = 0; k < graph[scc[i][j]].size(); ++k)
                {
                    connectto = graph[scc[i][j]][k];
                    if (group[connectto] != i) // connect to other scc
                    {
                        new_graph[i].push_back(group[connectto]); // add the direct scc edge
                        // printf("new_graph: (%d, %d)\n", scc[i][0], connectto);
                        out[i] = 1;
                        in[group[connectto]] = 1;
                    }
                }
            }
        }
        // find all reachable in0 and out0 scc pair
        std::vector<std::pair<int, int>> in_out;
        for (int i = 0; i < scc.size(); ++i)
        {
            if ((in[i] == 0) && (out[i] != 0)) // not isolated
            {
                for (int j = 0; j < scc.size(); ++j)
                {
                    if ((i != j) && ((in[j] != 0) && (out[j] == 0)) && (Connect(new_graph, i, j) == 1)) // make pair
                    {
                        out[j] = 1;
                        in[i] = 1;
                        in_out.push_back(std::make_pair(i, j));
                        // printf("Make pair 1: (%d, %d)\n", scc[i][0], scc[j][0]);
                        break;
                    }
                }
            }
        }
        // make circular
        int ss = in_out.size();
        for (int i = 0; i < ss - 1; ++i)
        {
            new_edge.push_back(std::make_pair(scc[in_out[i].second][0], scc[in_out[i + 1].first][0]));
            // printf("Add edge: (%d, %d)\n", scc[in_out[i].second][0], scc[in_out[i + 1].first][0]);
        }
        if (in_out.empty())
        {
            in_out.push_back(std::make_pair(0, 0));
            in[0] = 1;
            out[0] = 1;
        }
        int tail = scc[in_out[in_out.size() - 1].second][0];
        // add the isolated point
        for (int i = 0; i < scc.size(); ++i)
        {
            if ((in[i] == 0) && (out[i] == 0)) // isolated
            {
                in[i] = 1;
                out[i] = 1;
                new_edge.push_back(std::make_pair(tail, scc[i][0]));
                // printf("Add edge: (%d, %d)\n", tail, scc[i][0]);
                tail = scc[i][0];
            }
        }
        // add head and tail
        new_edge.push_back(std::make_pair(tail, scc[in_out[0].first][0]));
        // printf("Add edge: (%d, %d)\n", tail, scc[in_out[0].first][0]);
        //  arbitrarily make pair of the remaindings
        int find = 0;
        for (int i = 0; i < scc.size(); ++i)
        {
            if (in[i] == 0)
            {
                find = 0;
                for (int j = 0; j < scc.size(); ++j)
                {
                    if (out[j] == 0)
                    {
                        in[i] = 1;
                        out[j] = 1;
                        find = 1;
                        new_edge.push_back(std::make_pair(scc[j][0], scc[i][0]));
                        // printf("Add edge: (%d, %d)\n", scc[j][0], scc[i][0]);
                        break;
                    }
                }
                if (find == 0)
                {
                    in[i] = 1;
                    new_edge.push_back(std::make_pair(scc[in_out[0].second][0], scc[i][0]));
                    /// printf("Add edge: (%d, %d)\n", scc[in_out[0].second][0], scc[i][0]);
                }
            }
        }
        for (int i = 0; i < scc.size(); ++i)
        {
            if (out[i] == 0)
                new_edge.push_back(std::make_pair(scc[i][0], scc[in_out[0].first][0]));
        }
    }
}
void SCC(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &graph_T, std::vector<std::vector<int>> &graph_D, int N, std::vector<std::pair<int, int>> &new_edge)
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>> finish, finish2;
    std::vector<std::vector<int>> scc;
    int visit[N + 1], group[N + 1], v1[N + 1], v2[N + 1], scc_idx = 0;
    std::pair<int, int> temp;
    for (int i = 0; i < (N + 1); ++i)
        visit[i] = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (visit[i] == 0)
        {
            DFS(graph, i, N, finish, visit, v1);
            while (!finish.empty())
            {
                temp = finish.top();
                finish.pop();
                if (visit[i] == 0)
                {
                    DFS(graph_T, temp.second, N, finish2, visit, v2);
                    // add to scc
                    scc.push_back(std::vector<int>());
                    while (!finish2.empty()) // add to scc component
                    {
                        // insert to scc
                        temp = finish2.top();
                        finish2.pop();
                        if (v1[temp.second] == 1)
                        {
                            scc[scc_idx].push_back(temp.second);
                            // add to black list
                            visit[temp.second] = 1;
                            group[temp.second] = scc_idx;
                        }
                    }
                    scc_idx += 1;
                }
            }
        }
    }
    /*
        printf("SCC:\n");
        for (int i = 0; i < scc.size(); ++i)
        {
            for (int j = 0; j < scc[i].size(); ++j)
                printf("%d ", scc[i][j]);
            printf("\n");
        }
    */
    DAG(graph, graph_D, scc, group, new_edge);
}
int main()
{
    int testcase, flag, N, M, n1, n2;
    scanf("%d %d", &testcase, &flag);
    std::vector<std::vector<std::pair<int, int>>> new_edge;
    for (int t = 0; t < testcase; ++t)
    {
        scanf("%d %d", &N, &M);
        std::vector<std::vector<int>> graph, graph_T, graph_D;
        for (int i = 0; i < (N + 1); ++i)
        {
            graph.push_back(std::vector<int>());
            graph_T.push_back(std::vector<int>());
            graph_D.push_back(std::vector<int>());
        }
        for (int i = 0; i < M; ++i)
        {
            scanf("%d %d", &n1, &n2);
            graph[n1].push_back(n2);
            graph_T[n2].push_back(n1);
            graph_D[n1].push_back(n2);
            graph_D[n2].push_back(n1);
        }
        new_edge.push_back(std::vector<std::pair<int, int>>());
        SCC(graph, graph_T, graph_D, N, new_edge[t]);
    }
    for (int t = 0; t < testcase; ++t)
    {
        if (flag == 1)
        {
            if (new_edge[t].size() == 0)
                printf("%d", new_edge[t].size());
            else
                printf("%d\n", new_edge[t].size());
            for (int i = 0; i < new_edge[t].size(); ++i)
            {
                if (i == (new_edge[t].size() - 1))
                    printf("%d %d", new_edge[t][i].first, new_edge[t][i].second);
                else
                    printf("%d %d\n", new_edge[t][i].first, new_edge[t][i].second);
            }
        }
        else
            printf("%d", new_edge[t].size());
        if (t < (testcase - 1))
            printf("\n");
    }
}