#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
long long int answer;
struct Node
{
    int pos = 0;
    int cat = 0;
    int length = 0;
    int depth = 0;
    struct Node *pre;
};
struct Node *Newnode(int pos, int cat)
{
    struct Node *temp;
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->pre = NULL;
    temp->pos = pos;
    temp->cat = cat;
    temp->length = 1;
    temp->depth = 1;
    return temp;
}
long long int Crowdedness(std::map<int, struct Node *> &catx)
{
    std::map<int, struct Node *>::iterator it;
    long long int answer = 0, temp;
    for (it = catx.begin(); it != catx.end(); ++it)
    {
        temp = it->second->length;
        answer += temp * (temp - 1) / 2;
    }
    return answer;
}
void Place_Food(std::map<int, struct Node *> &catx, int pos, int rad)
{
    std::map<int, struct Node *>::iterator it, itn, pre;
    struct Node *t1;
    struct Node *t2;
    it = catx.lower_bound(pos - rad);
    if (it == catx.end())
        return;
    if (it->first > (pos + rad))
        return;
    else
    {
        t1 = it->second;
        pre = it;
        ++pre;
        answer -= (long long int)it->second->length * ((long long int)it->second->length - 1) / 2;
        catx.erase(it);
        it = pre;
        while ((it != catx.end()) && (it->first <= (pos + rad)))
        {
            t2 = it->second;
            answer -= (long long int)it->second->length * ((long long int)it->second->length - 1) / 2;
            if (t1->depth > t2->depth)
            {
                t2->pre = t1;
                t1->length += t2->length;
            }
            else
            {
                t1->pre = t2;
                t2->length += t1->length;
                if (t1->depth + 1 > t2->depth)
                    t2->depth = t1->depth + 1;
                t1 = t2;
            }
            pre = it;
            ++pre;
            catx.erase(it);
            it = pre;
        }
        catx.insert(std::make_pair(pos, t1));
        t1->pos = pos;
        answer += (long long int)t1->length * ((long long int)t1->length - 1) / 2;
    }
}
void Move_Cat(std::map<int, struct Node *> &catx, std::vector<struct Node *> &cat_pointer, int cat, int pos)
{
    // delete from oiginal group
    struct Node *temp = cat_pointer[cat];
    std::map<int, struct Node *>::iterator it;
    while (temp->pre != NULL)
        temp = temp->pre;
    temp->length -= 1;
    answer -= (long long int)temp->length;
    if (temp->length == 0)
    {
        it = catx.find(temp->pos);
        catx.erase(it);
    }

    // inset to right place
    temp = Newnode(pos, cat);
    cat_pointer[cat] = temp;
    it = catx.find(pos);
    if (it == catx.end())
        catx.insert(std::make_pair(pos, cat_pointer[cat]));
    else
    {
        struct Node *leader = it->second;
        answer += (long long int)leader->length;
        leader->length += 1;
        cat_pointer[cat]->pre = leader;
        if (2 > leader->depth)
            leader->depth = 2;
    }
    return;
}
int main()
{
    int N, Q, x;
    // std::set<std::pair<int, struct Node *>>
    scanf("%d %d", &N, &Q);
    std::map<int, struct Node *> catx; // cat position
    std::vector<struct Node *> cat_pointer(N + 1);
    std::map<int, struct Node *>::iterator it;
    long long int ans[Q];
    // catx.insert(std::make_pair(0, 0));
    struct Node *temp;
    for (int i = 0; i < N; ++i)
    {
        if (i == (N - 1))
            scanf("%d", &x);
        else
            scanf("%d ", &x);
        temp = Newnode(x, i + 1);
        cat_pointer[i + 1] = temp;
        it = catx.find(x);
        if (it == catx.end())
            catx.insert(std::make_pair(x, temp));
        else
        {
            struct Node *leader = it->second;
            leader->length += 1;
            temp->pre = leader;
            leader->depth = 2;
        }
    }
    answer = Crowdedness(catx);
    int action, a, b;
    for (int i = 0; i < Q; ++i)
    {
        scanf("%d %d %d", &action, &a, &b);
        if (action == 1) // place food at "a" with radius "b"
            Place_Food(catx, a, b);
        else if (action == 2) // move cat "a" to position "b"
            Move_Cat(catx, cat_pointer, a, b);

        // output crowdedness
        ans[i] = answer;
    }
    for (int i = 0; i < Q; ++i)
    {
        if (i == Q - 1)
            printf("%lld", ans[i]);
        else
            printf("%lld\n", ans[i]);
    }
}