#include <stdio.h>
#include <math.h>
#include <vector>

struct Node
{
    int index = 0;
    int pa = 0;
    int isroot = 0;
    long long int maxvalue = 0;
    struct Node *parent;
};

struct Node *Newnode()
{
    struct Node *temp;
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->parent = NULL;
    temp->index = 0;
    temp->pa = 0;
    temp->isroot = 0;
    temp->maxvalue = 0;
    return temp;
}

//Below Max function idea came up with GatherTown Discussion on the White Board.
struct Node *Max(int *S, struct Node *p, struct Node *n, struct Node *z, int id, long long int ptemp, long long int ntemp, long long ztemp) //p: same sign, n and z: others
{
    struct Node *temp = Newnode();
    temp->index = id;
    if (p->isroot == 1) // empty
    {
        //p[1] = id;
        temp->parent = p;
        temp->pa = 1;
        ptemp = S[id];
    }
    else if (S[id] > S[p->index]) //When the sign is same cut the p+ last and append new
    {
        ptemp -= S[p->index];
        ptemp += S[id];
    }
    if (n->isroot == 0)
        ntemp += S[id];
    if (z->isroot == 0)
        ztemp += S[id];
    if ((ptemp >= ntemp) && (ptemp >= ztemp))
    {
        if (p->isroot == 0) // parent not root
        {
            if (S[id] > S[p->index]) // cut the last and add new
            {
                //p[p[0]] = id; // change the last one id value
                temp->parent = p->parent;
                temp->pa = 1;
            }
            else
            {
                p->maxvalue = ptemp;
                return p;
            }
        }
        temp->maxvalue = ptemp;
        return temp;
    }
    else if ((ntemp >= ptemp) && (ntemp >= ztemp))
    {
        //for (int i = 1; i <= n[n[0]]; ++i)
        //    p[i] = n[i];
        //p[0] = n[0] + 1;
        //p[p[0]] = id;
        temp->parent = n;
        temp->pa = 1;
        temp->maxvalue = ntemp;
        return temp;
    }
    else
    {
        //for (int i = 1; i <= z[z[0]]; ++i)
        //    p[i] = z[i];
        //p[0] = z[0] + 1;
        //p[p[0]] = id;
        temp->parent = z;
        temp->pa = 1;
        temp->maxvalue = ztemp;
        return temp;
    }
    return temp;
}

int main()
{
    int testnum;
    int flag;
    int candynum;
    long long int pmax, nmax, zmax;
    scanf("%d %d", &testnum, &flag);
    long long int score[testnum];
    //std::vector<int>::iterator it(testnum);
    int *it[testnum];
    int ansnum[testnum];
    struct Node *p = Newnode();
    struct Node *n = Newnode();
    struct Node *z = Newnode();
    //struct Answer *answer = NewAnswer();
    for (int t = 0; t < testnum; ++t) // read each test case
    {
        scanf("%d", &candynum);
        int S[candynum + 1];
        int *ans = (int *)malloc((candynum) * sizeof(int));
        //int *p = (int *)malloc((candynum + 1) * sizeof(int));
        //int *n = (int *)malloc((candynum + 1) * sizeof(int));
        //int *z = (int *)malloc((candynum + 1) * sizeof(int));
        //p[0] = 0; //zero for the number in the list
        //n[0] = 0;
        //z[0] = 0;
        p->isroot = 1;
        n->isroot = 1;
        z->isroot = 1;
        pmax = -1LL << 63;
        nmax = -1LL << 63;
        zmax = -1LL << 63;
        for (int c = 1; c < candynum; ++c)
            scanf("%d ", &S[c]);
        scanf("%d", &S[candynum]);
        // solve each test case
        for (int i = 1; i <= candynum; ++i)
        {
            if (S[i] > 0)
            {
                p = Max(S, p, n, z, i, pmax, nmax, zmax);
                pmax = p->maxvalue;
            }
            else if (S[i] < 0)
            {
                n = Max(S, n, p, z, i, nmax, pmax, zmax);
                nmax = n->maxvalue;
            }
            else
            {
                z = Max(S, z, p, n, i, zmax, pmax, nmax);
                zmax = z->maxvalue;
            }
        }

        //empty
        if (p->isroot == 1)
            pmax = -1LL << 63;
        if (n->isroot == 1)
            nmax = -1LL << 63;
        if (z->isroot == 1)
            zmax = -1LL << 63;

        if ((pmax >= nmax) && (pmax >= zmax))
        {
            //printf("%lld\n", pmax);
            score[t] = pmax;
            ansnum[t] = 0;
            while (p->isroot == 0)
            {
                ans[ansnum[t]] = p->index;
                ansnum[t] += 1;
                p = p->parent;
            }

            it[t] = ans;
            //free(n);
            //free(z);
        }
        else if ((nmax >= pmax) && (nmax >= zmax))
        {
            //printf("%lld\n", nmax);
            score[t] = nmax;
            ansnum[t] = 0;
            while (n->isroot == 0)
            {
                ans[ansnum[t]] = n->index;
                ansnum[t] += 1;
                n = n->parent;
            }

            it[t] = ans;
            //free(p);
            //free(z);
        }
        else
        {
            //printf("%lld\n", zmax);
            score[t] = zmax;
            ansnum[t] = 0;
            while (z->isroot == 0)
            {
                ans[ansnum[t]] = z->index;
                ansnum[t] += 1;
                z = z->parent;
            }

            it[t] = ans;
            //free(p);
            //free(n);
        }
    }
    if (flag == 1)
    {
        for (int t = 0; t < testnum; ++t) // read each test case
        {
            printf("%lld\n", score[t]);
            printf("%d", ansnum[t]);
            for (int aa = 0; aa < ansnum[t]; ++aa)
                printf(" %d", *(it[t] + ansnum[t] - 1 - aa));
            if (t < (testnum - 1))
                printf("\n");
        }
    }
    else
    {
        for (int t = 0; t < testnum; ++t) // read each test case
            printf("%lld\n", score[t]);
    }
    return 0;
}