#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
struct node_depth
{
    int node;
    int depth;
};
node_depth BFS(std::vector<std::vector<int>> &graph, int start, int N, int *ancestor, std::vector<int> &leaf)
{
    node_depth answer;
    std::queue<int> bque;
    int depth[N + 1], color[N + 1];
    for (int i = 0; i < (N + 1); ++i)
        color[i] = 1; // avialible
    int u = start;
    int d = 0, child = 0;
    bque.push(u);
    color[u] = 0;
    depth[u] = 0;
    while (bque.size() > 0)
    {
        u = bque.front();
        bque.pop();
        d = depth[u];
        child = 0;
        for (int i = 0; i < graph[u].size(); ++i)
        {
            if (color[graph[u][i]] == 1)
            {
                child = 1;
                color[graph[u][i]] = 0;
                depth[graph[u][i]] = d + 1;
                ancestor[graph[u][i]] = u;
                bque.push(graph[u][i]);
            }
        }
        if (child == 0)
            leaf.push_back(u);
    }
    answer.node = u;
    answer.depth = depth[u];
    return answer;
}

int main()
{
    int N, n1, n2;
    scanf("%d", &N);
    // store graph using adjacency list
    std::vector<std::vector<int>> graph;
    for (int i = 0; i < (N + 1); ++i)
        graph.push_back(std::vector<int>());
    for (int i = 0; i < (N - 1); ++i)
    {
        scanf("%d %d", &n1, &n2);
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }
    int ancestor[N + 1];
    std::vector<int> leaft, leaf;
    node_depth bfs1 = BFS(graph, 1, N, ancestor, leaft);
    // printf("%d %d\n", bfs1.node, bfs1.depth);
    node_depth bfs2 = BFS(graph, bfs1.node, N, ancestor, leaf);
    // printf("%d %d\n", bfs2.node, bfs2.depth);
    int height[N + 1], onpath[N + 1];
    // node on the longest path
    for (int i = 0; i < (N + 1); ++i)
        onpath[i] = 0;
    int now = bfs2.node;
    for (int i = 0; i < (bfs2.depth + 1); ++i) // bfs2.depth+1 : num of node on the path
    {
        onpath[now] = 1;
        height[now] = 0; // initialize
        now = ancestor[now];
    }

    // update the height of node on the longest path
    int s = leaf.size();
    for (int i = 0; i < s; ++i)
    {
        int h = 0;
        now = leaf.back();
        // printf("leaf: %d\n", now);
        leaf.pop_back();
        while (1)
        {
            if (onpath[now] == 1)
            {
                if (height[now] < h)
                    height[now] = h;
                // printf("node: %d, height: %d\n", now, h);
                break;
            }
            now = ancestor[now];
            h += 1;
        }
    }
    int min = N + 1;
    int tempnum, templen, len1[bfs2.depth], len2[bfs2.depth], len1max = 0, len2max = 0;
    int reverse[N + 1];
    now = bfs2.node;
    for (int i = 0; i < bfs2.depth; ++i) // find longest path in the subgraph
    {
        reverse[ancestor[now]] = now;
        templen = i + height[now];
        if (templen > len1max)
            len1max = templen;
        len1[i] = len1max;
        now = ancestor[now];
    }
    for (int i = 0; i < bfs2.depth; ++i) // find longest path in the subgraph
    {
        templen = i + height[now];
        if (templen > len2max)
            len2max = templen;
        len2[i] = len2max;
        now = reverse[now];
    }

    for (int i = 0; i < bfs2.depth; ++i) // decide the cut edge
    {
        tempnum = int(std::ceil(float(len1[i]) / 2)) + int(std::ceil(float(len2[bfs2.depth - 1 - i]) / 2)) + 1; // farest path between tree
        // get max
        if ((len1[i] > tempnum) && (len1[i] > len2[bfs2.depth - 1 - i]))
            tempnum = len1[i];
        else if ((len2[bfs2.depth - 1 - i] > tempnum) && (len2[bfs2.depth - 1 - i] > len1[i]))
            tempnum = len2[bfs2.depth - 1 - i];
        // printf("len1: %d, len2: %d\n", len1[i], len2[bfs2.depth - 1 - i]);
        if (tempnum < min)
            min = tempnum;
    }
    /*
    int len1 = (bfs2.depth - 1) / 2;
    int len2 = bfs2.depth - 1 - len1;
    // printf("%d %d\n", len1, len2);
    int long1, long2, now;
    now = ancestor[bfs2.node];
    for (int i = 0; i < (len1 - 1); ++i)
    {
        now = ancestor[now];
    }
    // cut into 2 subgraphs
    // cut all "anc" edge except "now"
    std::vector<int> temparr;
    int s = graph[now].size();
    for (int i = 0; i < s; ++i)
    {
        if (graph[now].back() != ancestor[now])
            temparr.push_back(graph[now].back());
        graph[now].pop_back();
    }
    s = temparr.size();
    for (int i = 0; i < s; ++i)
    {
        graph[now].push_back(temparr.back());
        temparr.pop_back();
    }
    n1 = now;
    now = ancestor[now];
    // cut all "anc" edge except "ancestor[anc]"
    s = graph[now].size();
    for (int i = 0; i < s; ++i)
    {
        if (graph[now].back() != n1)
            temparr.push_back(graph[now].back());
        graph[now].pop_back();
    }
    s = temparr.size();
    for (int i = 0; i < s; ++i)
    {
        graph[now].push_back(temparr.back());
        temparr.pop_back();
    }
    n2 = now;
    // printf("cut point: %d %d\n", n1, n2);
    //  find 2 subgraphs' depth
    bfs1 = BFS(graph, n1, N, ancestor);
    bfs1 = BFS(graph, bfs1.node, N, ancestor);
    bfs2 = BFS(graph, n2, N, ancestor);
    bfs2 = BFS(graph, bfs2.node, N, ancestor);
    // printf("%d %d\n", bfs1.depth, bfs2.depth);
    // printf("end node: %d %d\n", bfs1.node, bfs2.node);
    if ((bfs1.node != n1) && (bfs2.node == n2))
    {
        int distance = bfs1.depth - len1;
    }
    else if ((bfs1.node == n1) && (bfs2.node != n2))
    {
        int distance = bfs2.depth - len2;
        bfs1.depth -= distance;
    }
    else if ((bfs1.node == n1) && (bfs2.node == n2))
    {
        if ((bfs1.depth % 2) != 0)
        {
            bfs1.depth -= 1;
            bfs2.depth += 1;
        }
    }
    int answer = int(std::ceil(float(bfs1.depth) / 2)) + int(std::ceil(float(bfs2.depth) / 2)) + 1;
        */
    printf("%d", min);
}