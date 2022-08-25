#include "ada-hw4-p3.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
// cd /mnt/d/大學/大五/大五上/演算法設計與分析/HW4/ada-hw4-p3/cpp
//  feel free to use global variables
std::vector<int> contest;          // each position, store id in the position
std::vector<int> conceal_s;        // store conceal id
std::vector<int> is_conceal;       // each position, weather the position is conceal
std::vector<int> conceal_pos;      // each position, the position of conceal position in conceal vector
std::vector<int> conceal_together; // each position, the id conceal together
std::vector<int> id_pos;
void Info()
{
    printf("[conceal_s]: ");
    for (int i = 0; i < conceal_s.size(); ++i)
        printf("%d ", conceal_s[i]);
    printf("\n");
    printf("[contest]: ");
    for (int i = 0; i < contest.size(); ++i)
        printf("%d ", contest[i]);
    printf("\n");
    printf("[is_conceal]: ");
    for (int i = 0; i < is_conceal.size(); ++i)
        printf("%d ", is_conceal[i]);
    printf("\n");
    printf("[conceal_pos]: ");
    for (int i = 0; i < conceal_pos.size(); ++i)
        printf("%d ", conceal_pos[i]);
    printf("\n");
    printf("[conceal_together]: ");
    for (int i = 0; i < conceal_together.size(); ++i)
        printf("%d ", conceal_together[i]);
    printf("\n");
    printf("[id_pos]: ");
    for (int i = 0; i < id_pos.size(); ++i)
        printf("%d ", id_pos[i]);
    printf("\n");
    return;
}
std::vector<int> init(int N)
{
    contest.resize(N);
    is_conceal.resize(N);
    conceal_pos.resize(N);
    conceal_together.resize(N);
    id_pos.resize(N);

    int notconceal = -1;
    for (int i = 0; i < N; ++i)
    {
        contest[i] = i;
        is_conceal[i] = 0;
        conceal_pos[i] = -1;
        conceal_together[i] = -1;
        id_pos[i] = i;
    }
    for (int i = 1; i < N; ++i)
    {
        // find the pre
        notconceal = -1;
        int idx = i - 1;
        while (idx >= 0)
        {
            if (is_conceal[idx] == 0)
            {
                notconceal = idx;
                break;
            }
            idx--;
        }
        if ((notconceal >= 0) && (!compare(contest[notconceal], contest[i])))
        {
            conceal_pos[notconceal] = conceal_s.size();
            is_conceal[notconceal] = 1;
            conceal_s.push_back(notconceal);

            conceal_pos[i] = conceal_s.size();
            is_conceal[i] = 1;
            conceal_s.push_back(i);

            conceal_together[notconceal] = i;
            conceal_together[i] = notconceal;
        }
    }
    // Info();
    return conceal_s;
}
int previous(int idx)
{
    int pre = -1;
    while (idx >= 0)
    {
        if (is_conceal[idx] == 0)
        {
            pre = idx;
            break;
        }
        --idx;
    }
    return pre;
}
int nextp(int idx)
{
    int next = -1;
    while (idx < contest.size())
    {
        if (is_conceal[idx] == 0)
        {
            next = idx;
            break;
        }
        ++idx;
    }
    return next;
}
std::vector<int> insert(int p, int id)
{
    // printf("Insert: (p, id) = %d, %d\n", p, id);
    contest.insert(contest.begin() + p, id);
    is_conceal.insert(is_conceal.begin() + p, 0);
    conceal_pos.insert(conceal_pos.begin() + p, -1);
    conceal_together.insert(conceal_together.begin() + p, -1);
    id_pos.push_back(p);
    for (int i = 0; i < id_pos.size() - 1; ++i)
    {
        if (id_pos[i] >= p)
            id_pos[i] += 1;
        // printf("%d ", id_pos[i]);
    }
    // printf("\n");

    int pre = previous(p - 1);
    int next = nextp(p + 1);

    if ((next == -1) && (pre >= 0) && (!compare(contest[pre], contest[p])))
    {
        // printf("put in conceal: %d\n", contest[p]);
        conceal_pos[p] = conceal_s.size();
        is_conceal[p] = 1;
        conceal_s.push_back(id);

        conceal_pos[pre] = conceal_s.size();
        is_conceal[pre] = 1;
        conceal_s.push_back(contest[pre]);

        conceal_together[p] = contest[pre];
        conceal_together[pre] = contest[p];
    }
    else if ((next >= 0) && (pre == -1) && (!compare(contest[p], contest[next])))
    {
        // printf("put in conceal: %d\n", contest[p]);
        conceal_pos[p] = conceal_s.size();
        is_conceal[p] = 1;
        conceal_s.push_back(id);

        conceal_pos[next] = conceal_s.size();
        is_conceal[next] = 1;
        conceal_s.push_back(contest[next]);

        conceal_together[p] = contest[next];
        conceal_together[next] = contest[p];
    }
    else if ((next >= 0) && (pre >= 0))
    {
        int pp = compare(contest[pre], contest[p]);
        int nn = compare(contest[p], contest[next]);
        if ((pp == 0) || (nn == 0))
        {
            // printf("put in conceal: %d\n", contest[p]);
            conceal_pos[p] = conceal_s.size();
            is_conceal[p] = 1;
            conceal_s.push_back(id);

            if (pp == 0)
            {
                conceal_pos[pre] = conceal_s.size();
                is_conceal[pre] = 1;
                conceal_s.push_back(contest[pre]);

                conceal_together[p] = contest[pre];
                conceal_together[pre] = contest[p];
            }
            else
            {
                conceal_pos[next] = conceal_s.size();
                is_conceal[next] = 1;
                conceal_s.push_back(contest[next]);

                conceal_together[p] = contest[next];
                conceal_together[next] = contest[p];
            }
        }
    }
    // Info();
    return conceal_s;
}

std::vector<int> remove(int p)
{
    // printf("Remove: (p) = %d\n", p);
    for (int i = 0; i < id_pos.size(); ++i)
    {
        if (id_pos[i] > p)
            id_pos[i] -= 1;
        else if (id_pos[i] == p)
            id_pos[i] = -1;
    }
    contest.erase(contest.begin() + p);
    int is_con = is_conceal[p];
    is_conceal.erase(is_conceal.begin() + p);
    int con_pos = conceal_pos[p];
    conceal_pos.erase(conceal_pos.begin() + p);
    int together = conceal_together[p]; // together id
    conceal_together.erase(conceal_together.begin() + p);

    if (is_con == 1)
    {
        for (int i = 0; i < conceal_pos.size(); ++i)
        {
            if (conceal_pos[i] > con_pos)
                conceal_pos[i] -= 1;
        }
        conceal_s.erase(conceal_s.begin() + con_pos);
        if (together >= 0) // weather to move out point from conceal
        {
            // printf("together: id: %d, pos: %d\n", together, id_pos[together]);
            conceal_together[id_pos[together]] = -1;
            int pre = previous(id_pos[together] - 1);
            int next = nextp(id_pos[together] + 1);
            int pp = -1;
            int nn = -1;
            if (pre >= 0)
                pp = compare(contest[pre], together);
            if (next >= 0)
                nn = compare(together, contest[next]);
            if ((pre >= 0) && (next == -1))
            {
                // printf("move out conceal: %d\n", contest[together]);
                if (pp == 1)
                {
                    conceal_s.erase(conceal_s.begin() + conceal_pos[id_pos[together]]);
                    is_conceal[id_pos[together]] = 0;
                    for (int i = 0; i < conceal_pos.size(); ++i)
                    {
                        if (conceal_pos[i] > conceal_pos[id_pos[together]])
                            conceal_pos[i] -= 1;
                    }
                    conceal_pos[id_pos[together]] = -1;
                }
                else
                {
                    conceal_pos[pre] = conceal_s.size();
                    is_conceal[pre] = 1;
                    conceal_s.push_back(contest[pre]);

                    conceal_together[id_pos[together]] = contest[pre];
                    conceal_together[pre] = together;
                }
            }
            else if ((pre == -1) && (next >= 0))
            {
                if (nn == 1)
                {
                    // printf("move out conceal: %d\n", contest[together]);
                    conceal_s.erase(conceal_s.begin() + conceal_pos[id_pos[together]]);
                    is_conceal[id_pos[together]] = 0;
                    for (int i = 0; i < conceal_pos.size(); ++i)
                    {
                        if (conceal_pos[i] > conceal_pos[id_pos[together]])
                            conceal_pos[i] -= 1;
                    }
                    conceal_pos[id_pos[together]] = -1;
                }
                else
                {
                    conceal_pos[next] = conceal_s.size();
                    is_conceal[next] = 1;
                    conceal_s.push_back(contest[next]);

                    conceal_together[id_pos[together]] = contest[next];
                    conceal_together[next] = together;
                }
            }
            else if ((pre >= 0) && (next >= 0))
            {
                if ((pp == 1) && (nn == 1))
                {
                    // printf("move out conceal: %d\n", contest[together]);
                    conceal_s.erase(conceal_s.begin() + conceal_pos[id_pos[together]]);
                    is_conceal[id_pos[together]] = 0;
                    for (int i = 0; i < conceal_pos.size(); ++i)
                    {
                        if (conceal_pos[i] > conceal_pos[id_pos[together]])
                            conceal_pos[i] -= 1;
                    }
                    conceal_pos[id_pos[together]] = -1;
                }
                else
                {
                    if (pp == 0)
                    {
                        conceal_pos[pre] = conceal_s.size();
                        is_conceal[pre] = 1;
                        conceal_s.push_back(contest[pre]);

                        conceal_together[id_pos[together]] = contest[pre];
                        conceal_together[pre] = together;
                    }
                    else
                    {
                        conceal_pos[next] = conceal_s.size();
                        is_conceal[next] = 1;
                        conceal_s.push_back(contest[next]);

                        conceal_together[id_pos[together]] = contest[next];
                        conceal_together[next] = together;
                    }
                }
            }
            else if ((pre == -1) && (next == -1))
            {
                conceal_s.erase(conceal_s.begin() + conceal_pos[id_pos[together]]);
                is_conceal[id_pos[together]] = 0;
                for (int i = 0; i < conceal_pos.size(); ++i)
                {
                    if (conceal_pos[i] > conceal_pos[id_pos[together]])
                        conceal_pos[i] -= 1;
                }
                conceal_pos[id_pos[together]] = -1;
            }
        }
    }
    // Info();

    return conceal_s;
}
