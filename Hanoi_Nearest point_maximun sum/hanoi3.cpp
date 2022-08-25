#include <stdio.h>
#include <math.h>

unsigned long long int remain_step;
unsigned long long int POW(int pow)
{
    unsigned long long int ans;
    if (pow <= 63)
        return (((unsigned long long int)1 << pow) % (unsigned long long int)998244353);
    else
        ans = (unsigned long long int)(POW(pow - 30) * (unsigned long long int)1 << 30) % (unsigned long long int)998244353;
    return ans;
}
//Below Hanoi function idea came up with GatherTown Discussion on the White Board.
int Hanoi(int N, int *A, int s, int r, int d) //source/ remainder/ destination
{
    int answer = 0;
    if (N == 1)
    {
        if (A[N] == d)
            return 1;
        else if (A[N] == s)
        {
            remain_step += (unsigned long long int)1;
            remain_step = (unsigned long long int)(remain_step % (unsigned long long int)998244353);
            return 1;
        }
        else
            return -1;
    }

    if (A[N] == d)
        answer = Hanoi(N - 1, A, r, s, d);
    else if (A[N] == s)
    {
        answer = Hanoi(N - 1, A, s, d, r);
        if ((N - 1) <= 63) //not overflow
        {
            remain_step += (unsigned long long int)(((unsigned long long int)((unsigned long long int)1 << ((unsigned long long int)N - (unsigned long long int)1))) % (unsigned long long int)998244353); // % (long long int)998244353); // (pow(2, N-1) - 1) + 1
            //remain_step += pow((long long int)2, N - (long long int)1) % (long long int)998244353;
            remain_step = (unsigned long long int)(remain_step % (unsigned long long int)998244353);
        }
        else
        {
            remain_step += POW(N - 1);
            remain_step = (unsigned long long int)(remain_step % (unsigned long long int)998244353);
        }
    }
    else
        return -1;

    return answer;
}
int main()
{
    //unsigned long long int k = POW(64);
    //printf("%llu", k);
    //remain_step = (pow(2, 33) - 1) % 33;
    //printf("%lld", remain_step);

    remain_step = (unsigned long long int)0;
    int disk_num;
    scanf("%d", &disk_num);
    int A[disk_num + 1]; // add 1 for convience, index: the disk num, value: the peg it's on
    for (int i = 0; i < disk_num + 1; ++i)
        A[i] = 0;
    int a, temp;
    int peg_min = disk_num + 1;
    int last[3];
    int bad = 0;
    for (int i = 0; i < 3; ++i) //can't (1) repeat (2) not equal to disk_num (3) reverse
    {
        scanf("%d", &a);
        peg_min = disk_num + 1;
        for (int j = 0; j < a; ++j)
        {
            scanf(" %d", &temp);

            if (temp > peg_min) // number can't reverse
                bad = 1;
            else
                peg_min = temp;

            if (A[temp] == 0) // disk cannot repeat
            {
                A[temp] = i + 1;
                last[i] = temp;
            }
            else
                bad = 1;
        }
    }

    if (bad == 1)
    {
        printf("-1");
        return 0;
    }

    if (Hanoi(disk_num, A, 1, 2, 3) == 1)
        printf("%llu", remain_step);
    else
        printf("-1");
    return 0;
}