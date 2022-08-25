#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
#include <set>
#include <limits>
void Decrease_key(std::priority_queue<std::tuple<long long int, int, int>, std::vector<std::tuple<long long int, int, int>>, std::greater<std::tuple<long long int, int, int>>> &dijk, int n2, long long int newdis, int edgenum, int *version)
{
    dijk.push(std::make_tuple(newdis, n2, edgenum));
    version[n2] = edgenum;
    return;
}
void RELAX(int n1, int n2, long long int n1_n2, int edgenum, std::priority_queue<std::tuple<long long int, int, int>, std::vector<std::tuple<long long int, int, int>>, std::greater<std::tuple<long long int, int, int>>> &dijk, long long int *distance, int *version)
{
    long long int newdis = distance[n1] + n1_n2;
    if (distance[n2] >= newdis)
    {
        Decrease_key(dijk, n2, newdis, edgenum, version);
        distance[n2] = newdis;
    }
    return;
}
void DIJKSTRA(int N, int M, int *InEdge, std::vector<std::vector<std::tuple<int, int, int>>> &graph)
{
    std::priority_queue<std::tuple<long long int, int, int>, std::vector<std::tuple<long long int, int, int>>, std::greater<std::tuple<long long int, int, int>>> dijk;
    long long int distance[N + 1];
    int version[N + 1];
    int InSet[N + 1];
    int EdgeNum = 0;
    for (int i = 1; i < (M + 1); ++i)
        InEdge[i] = 0;
    // starting point
    dijk.push(std::make_tuple(0, 1, 0));
    distance[1] = 0;
    InSet[1] = 0;
    version[1] = 0;
    for (int i = 2; i < (N + 1); ++i)
    {
        dijk.push(std::make_tuple(std::numeric_limits<long long>::max(), i, 0));
        distance[i] = std::numeric_limits<long long>::max();
        InSet[i] = 0;
        version[i] = 0;
    }
    std::tuple<long long int, int, int> node;
    while (dijk.size() != 0)
    {
        //########### find the newest insert ##############
        while (1) //(std::get<0>(node) == temp)
        {
            node = dijk.top();
            dijk.pop();
            if (std::get<2>(node) == version[std::get<1>(node)])
                break;
        }
        //###########################
        if (InSet[std::get<1>(node)] == 0)
        {
            // printf("node:%d, cost:%lld\n", std::get<1>(node), std::get<0>(node));
            InSet[std::get<1>(node)] = 1;
            InEdge[std::get<2>(node)] = 1;
            EdgeNum += 1;
            for (int i = 0; i < graph[std::get<1>(node)].size(); ++i)
                RELAX(std::get<1>(node), std::get<0>(graph[std::get<1>(node)][i]), std::get<1>(graph[std::get<1>(node)][i]), std::get<2>(graph[std::get<1>(node)][i]), dijk, distance, version);
        }
        if (EdgeNum == N)
            break;
    }
    return;
}
int Findset(int *valid_set, std::vector<std::set<int>> &setvec, int M, int target)
{
    std::set<int>::iterator it;
    for (int i = 1; i < (M + 1); ++i)
    {
        if (valid_set[i] == 1)
        {
            it = setvec[i].find(target);
            if (it != setvec[i].end()) // found
                return i;              // return the set number
        }
    }
    printf("Might not happend!\n");
    return -1;
}
void UnionSet(int *valid_set, std::vector<std::set<int>> &setvec, int set1, int set2)
{
    std::set<int>::iterator it;
    if (setvec[set1].size() < setvec[set2].size())
    {
        valid_set[set1] = 0;
        for (it = setvec[set1].begin(); it != setvec[set1].end(); ++it)
            setvec[set1].insert(*it);
    }
    else
    {
        valid_set[set2] = 0;
        for (it = setvec[set2].begin(); it != setvec[set2].end(); ++it)
            setvec[set1].insert(*it);
    }
}
int Findset2(int target, int *group)
{
    int temp = target;
    while (group[temp] != -1)
        temp = group[temp];
    return temp;
}
void UnionSet2(int set1, int set2, int *group)
{
    group[set1] = set2;
    return;
}
void Kruskal(int N, int M, int *InEdge, std::priority_queue<std::tuple<int, int, int, int>, std::vector<std::tuple<int, int, int, int>>, std::greater<std::tuple<int, int, int, int>>> &minqueue)
{
    // std::vector<std::set<int>> set_vector;
    // int valid_set[N + 1];
    int group[N + 1];
    int EdgeNum = 0;
    for (int i = 1; i < (M + 1); ++i)
        InEdge[i] = 0;
    for (int i = 0; i < (N + 1); ++i)
    {
        // set_vector.push_back(std::set<int>());
        // set_vector[i].insert(i);
        // valid_set[i] = 1;
        group[i] = -1;
    }
    std::tuple<int, int, int, int> minedge;
    int set1, set2;
    while (!minqueue.empty())
    {
        minedge = minqueue.top();
        minqueue.pop();
        set1 = Findset2(std::get<1>(minedge), group); // Findset(valid_set, set_vector, M, std::get<1>(minedge));
        set2 = Findset2(std::get<2>(minedge), group); // Findset(valid_set, set_vector, M, std::get<2>(minedge));
        if (set1 != set2)
        {
            // printf("n1:%d, n2:%d, cost:%d\n", std::get<1>(minedge), std::get<2>(minedge), std::get<0>(minedge));
            InEdge[std::get<3>(minedge)] = 1;
            EdgeNum += 1;
            UnionSet2(set1, set2, group); // UnionSet(valid_set, set_vector, set1, set2);
        }
        if (EdgeNum == N - 1)
            break;
    }
}
int Prim(int N, int M, int *InEdge, int *InEdge_Short, std::vector<std::vector<std::tuple<int, int, int>>> &graph)
{
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> prim;
    int key[N + 1];
    int InSet[N + 1];
    int EdgeNum = 0;
    for (int i = 1; i < (M + 1); ++i)
        InEdge[i] = 0;
    // starting point
    prim.push(std::make_tuple(0, 1, 0));
    key[1] = 0;
    InSet[1] = 0;
    for (int i = 2; i < (N + 1); ++i)
    {
        prim.push(std::make_tuple(2147483647, i, 0));
        key[i] = 2147483647;
        InSet[i] = 0;
    }
    std::tuple<int, int, int> node, node_temp;
    std::vector<std::tuple<int, int, int>> tempvec;
    int temp;
    int u, v, cost, edge;
    while (prim.size() != 0)
    {
        node = prim.top();
        prim.pop();
        if (InSet[std::get<1>(node)] == 0)
        {
            //########### check anawer ##############
            // whether forms a minimum spanning tree
            temp = std::get<0>(node);
            while (InEdge_Short[std::get<2>(node)] == 0)
            {
                tempvec.push_back(node);
                node = prim.top();
                prim.pop();
                if (std::get<0>(node) > temp) // fail
                    return -1;
            }
            // inset back
            while (tempvec.size() != 0)
            {
                node_temp = tempvec.back();
                tempvec.pop_back();
                prim.push(node_temp);
            }
            //###########################
            // printf("node:%d, cost:%d\n", std::get<1>(node), std::get<0>(node));
            InSet[std::get<1>(node)] = 1;
            InEdge[std::get<2>(node)] = 1;
            EdgeNum += 1;
            for (int i = 0; i < graph[std::get<1>(node)].size(); ++i)
            {
                u = std::get<1>(node);
                v = std::get<0>(graph[u][i]);
                cost = std::get<1>(graph[u][i]);
                edge = std::get<2>(graph[u][i]);
                if (cost <= key[v])
                {
                    key[v] = cost;
                    prim.push(std::make_tuple(key[v], v, edge));
                }
            }
        }
        if (EdgeNum == N)
            break;
    }
    if (EdgeNum != N)
        return -1;
    return 1;
}
int main()
{
    int N, M, n1, n2, cost;
    scanf("%d %d", &N, &M);
    std::priority_queue<std::tuple<int, int, int, int>, std::vector<std::tuple<int, int, int, int>>, std::greater<std::tuple<int, int, int, int>>> mst;
    // store graph using adjacency list
    std::vector<std::vector<std::tuple<int, int, int>>> graph;
    for (int i = 0; i < (N + 1); ++i)
        graph.push_back(std::vector<std::tuple<int, int, int>>());
    for (int i = 1; i < (M + 1); ++i)
    {
        scanf("%d %d %d", &n1, &n2, &cost);
        mst.push(std::make_tuple(cost, n1, n2, i));
        graph[n1].push_back(std::make_tuple(n2, cost, i));
        graph[n2].push_back(std::make_tuple(n1, cost, i));
    }
    int InEdge_short[M + 1];
    int InEdge_mst[M + 1];
    // Kruskal(N, M, InEdge_mst, mst);
    DIJKSTRA(N, M, InEdge_short, graph);
    int same = Prim(N, M, InEdge_mst, InEdge_short, graph);
    if (same == -1)
        printf("No");
    else
    {
        printf("Yes\n");
        // output answer
        int first = 1;
        for (int i = 1; i < (M + 1); i++)
        {
            if (InEdge_short[i] == 1)
            {
                if (first == 1)
                {
                    printf("%d", i);
                    first = 0;
                }
                else
                    printf(" %d", i);
            }
        }
    }
}