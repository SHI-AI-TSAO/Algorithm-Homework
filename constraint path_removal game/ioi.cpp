#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
struct Answer
{
    long long int revenue;
    int remain;
};
Answer InsertTask(int *s, int *e, int *xx, int *p, int *index, int N, int NN)
{
    Answer ans;
    long long int revenue = 0;
    int remain = 0;
    std::vector<int> x(NN);
    for (int i = 0; i < NN; ++i)
        x[i] = xx[i];
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> split;
    for (int i = 0; i < N; ++i)
        split.push(std::make_tuple(s[index[i]], index[i], 0)); // 0 for start time
    for (int i = 0; i < N; ++i)
        split.push(std::make_tuple(e[index[i]] + 1, index[i], 1));                                                         // 1 for end time
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> section; //, std::greater<std::pair<int, std::pair<int, int>>>
    int start, sec_day;
    std::tuple<int, int, int> temp;
    //  first start task
    temp = split.top();
    split.pop();
    start = std::get<0>(temp);
    // printf("At time %d\n", start);
    section.push(std::make_pair(e[std::get<1>(temp)], std::get<1>(temp)));
    // printf("push into section: task: %d, endtime: %d\n", std::get<1>(temp), e[std::get<1>(temp)]);
    for (int i = 1; i < 2 * N; ++i)
    {
        temp = split.top();
        split.pop();
        if (std::get<2>(temp) == 0) // new join task
        {
            sec_day = std::get<0>(temp) - start;
            start = std::get<0>(temp);
            // printf("At time %d\n", start);
            if (section.size() > 0)
            {
                std::pair<int, int> section_top = section.top(); // consider the top (first end)
                int t = section_top.second;
                while (sec_day > 0) // add revenue
                {
                    if (x[t] <= sec_day)
                    {
                        revenue += ((long long int)p[t]) * ((long long int)x[t]);
                        sec_day -= x[t];
                        x[t] = 0;
                        section.pop(); // use all and pop
                        // printf("pop out section: task: %d\n", t);
                        if (section.size() == 0)
                            break;
                        section_top = section.top(); // next to use
                        t = section_top.second;
                    }
                    else
                    {
                        revenue += ((long long int)p[t]) * ((long long int)sec_day);
                        x[t] -= sec_day;
                        break;
                    }
                }
            }
            section.push(std::make_pair(e[std::get<1>(temp)], std::get<1>(temp))); // add into section
                                                                                   // printf("push into section: task: %d, endtime: %d\n", std::get<1>(temp), e[std::get<1>(temp)]);
            // printf("revenue: %lld\n", revenue);
        }
        else // task meet deadline
        {
            sec_day = std::get<0>(temp) - start;
            start = std::get<0>(temp);
            // printf("At time %d\n", start);
            if (section.size() > 0)
            {
                std::pair<int, int> section_top = section.top(); // consider the top (first end)
                int t = section_top.second;
                while (sec_day > 0) // add revenue
                {
                    if (x[t] <= sec_day)
                    {
                        revenue += ((long long int)p[t]) * ((long long int)x[t]);
                        sec_day -= x[t];
                        x[t] = 0;
                        section.pop(); // use all and pop
                        // printf("pop out section: task: %d\n", t);
                        if (section.size() == 0)
                            break;
                        section_top = section.top(); // next to use
                        t = section_top.second;
                    }
                    else
                    {
                        revenue += ((long long int)p[t]) * ((long long int)sec_day);
                        x[t] -= sec_day;
                        break;
                    }
                }
            }
            if (section.size() > 0)
            {
                std::pair<int, int> section_top = section.top(); // consider the top (first end)
                if (section_top.second == std::get<1>(temp))
                {
                    remain += x[section_top.second];
                    // printf("pop out section: task: %d\n", section_top.second);
                    section.pop();
                }
            }
        }
    }
    ans.revenue = revenue;
    // count the remain task
    while (section.size() > 0)
    {
        std::pair<int, int> section_top = section.top();
        section.pop();
        remain += x[section_top.second];
    }
    ans.remain = remain;
    // free memory
    std::vector<int>().swap(x);
    return ans;
}
int main()
{
    int N;
    scanf("%d", &N);
    int s[N], e[N], x[N], p[N], index[N];
    long long int revenue = 0;
    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d %d %d", &s[i], &e[i], &x[i], &p[i]);
        index[i] = i;
    }
    std::sort(index, index + N, [&](int n1, int n2)
              { return p[n1] > p[n2]; });
    // Insert the max
    Answer temp;
    for (int i = 0; i < N; i++)
    {
        temp = InsertTask(s, e, x, p, index, i + 1, N);
        x[index[i]] -= temp.remain;
        revenue += (long long int)p[index[i]] * (long long int)x[index[i]];
        // printf("%lld\n", revenue);
    }
    printf("%lld", revenue);
    return 0;
}