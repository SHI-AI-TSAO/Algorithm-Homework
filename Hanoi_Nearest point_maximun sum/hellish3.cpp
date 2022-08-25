#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>

long int score;
double a, b, c;
//long long int deep;

void Compare(long int *z, long int *index, long int start, long int mid, long int last)
{
    //printf("compare\n");
    long int *ztemp = (long int *)malloc((last - start + (long int)1) * sizeof(long int));
    long int *idtemp = (long int *)malloc((last - start + (long int)1) * sizeof(long int));
    long int pt1 = start;
    long int pt2 = mid + (long int)1;
    long int temp_index = (long int)0;

    while (1)
    {
        if (z[pt1] <= z[pt2])
        {
            ztemp[temp_index] = z[pt1];
            idtemp[temp_index] = index[pt1];
            pt1 += (long int)1;
        }
        else
        {
            ztemp[temp_index] = z[pt2];
            idtemp[temp_index] = index[pt2];
            pt2 += (long int)1;
        }
        temp_index += (long int)1;

        if (pt1 > mid)
        {
            while (pt2 <= last)
            {
                ztemp[temp_index] = z[pt2];
                idtemp[temp_index] = index[pt2];
                pt2 += (long int)1;
                temp_index += (long int)1;
            }
            break;
        }
        else if (pt2 > last)
        {
            while (pt1 <= mid)
            {
                ztemp[temp_index] = z[pt1];
                idtemp[temp_index] = index[pt1];
                pt1 += (long int)1;
                temp_index += (long int)1;
            }
            break;
        }
    }

    for (long int i = start; i <= last; ++i)
    {
        z[i] = ztemp[i - start];
        index[i] = idtemp[i - start];
        //printf("%ld(%ld) ", z[i], index[i]);
    }
    //printf("\n");
    //printf("end compare\n");
    free(ztemp);
    free(idtemp);
    return;
}
void Merge(long int *z, long int *index, long int start, long int last)
{
    //printf("merge\n");
    if (start >= last)
        return;
    long int mid = (long int)((start + last) / (long int)2);
    Merge(z, index, start, mid);
    Merge(z, index, mid + (long int)1, last);
    Compare(z, index, start, mid, last);
    //printf("end merge\n");
    return;
}

void pure_Compare(double *z, long int start, long int mid, long int last)
{
    //printf("compare\n");
    long int *ztemp = (long int *)malloc((last - start + (long int)1) * sizeof(long int));
    long int pt1 = start;
    long int pt2 = mid + (long int)1;
    long int temp_index = (long int)0;

    while (1)
    {
        if (z[pt1] <= z[pt2])
        {
            ztemp[temp_index] = z[pt1];
            pt1 += (long int)1;
        }
        else
        {
            ztemp[temp_index] = z[pt2];
            pt2 += (long int)1;
        }
        temp_index += (long int)1;

        if (pt1 > mid)
        {
            while (pt2 <= last)
            {
                ztemp[temp_index] = z[pt2];
                pt2 += (long int)1;
                temp_index += (long int)1;
            }
            break;
        }
        else if (pt2 > last)
        {
            while (pt1 <= mid)
            {
                ztemp[temp_index] = z[pt1];
                pt1 += (long int)1;
                temp_index += (long int)1;
            }
            break;
        }
    }

    for (long int i = start; i <= last; ++i)
        z[i] = ztemp[i - start];

    free(ztemp);
    return;
}
void pure_Merge(double *z, long int start, long int last)
{
    if (start >= last)
        return;
    long int mid = (long int)((start + last) / (long int)2);
    pure_Merge(z, start, mid);
    pure_Merge(z, mid + (long int)1, last);
    pure_Compare(z, start, mid, last);
    return;
}

//Below Merge2&Compare2 function idea came up with GatherTown Discussion on the White Board.
void Compare2(double *pn, long int start, long int mid, long int last)
{
    //printf("compare\n");
    double *pntemp = (double *)malloc((last - start + (long int)1) * sizeof(double));
    long int pt1 = start;
    long int pt2 = mid + (long int)1;
    long int temp_index = (long int)0;
    if ((double)b / a >= (double)0)
    {
        while (1)
        {
            if (pn[pt1] * b / a + c / a < pn[pt2])
            {
                score += last - pt2 + (long int)1;
                pt1 += (long int)1;
            }
            else
                pt2 += (long int)1;
            if (pt1 > mid)
                break;
            else if (pt2 > last)
                break;
        }
    }
    else // inverse compare
    {
        pt1 = mid;
        pt2 = mid + (long int)1;
        last;
        while (1)
        {
            if (pn[pt1] * b / a + c / a < pn[pt2])
            {
                score += last - pt2 + (long int)1;
                pt1 -= (long int)1;
            }
            else
                pt2 += (long int)1;
            if (pt1 < start)
                break;
            else if (pt2 > last)
                break;
        }
    }

    pt1 = start;
    pt2 = mid + (long int)1;
    temp_index = (long int)0;
    while (1)
    {
        if (pn[pt1] < pn[pt2])
        {
            pntemp[temp_index] = pn[pt1];
            pt1 += (long int)1;
        }
        else
        {
            pntemp[temp_index] = pn[pt2];
            pt2 += (long int)1;
        }
        temp_index += (long int)1;

        if (pt1 > mid)
        {
            while (pt2 <= last)
            {
                pntemp[temp_index] = pn[pt2];
                pt2 += (long int)1;
                temp_index += (long int)1;
            }
            break;
        }
        else if (pt2 > last)
        {
            while (pt1 <= mid)
            {
                pntemp[temp_index] = pn[pt1];
                pt1 += (long int)1;
                temp_index += (long int)1;
            }
            break;
        }
    }

    for (long int i = start; i <= last; ++i)
    {
        pn[i] = pntemp[i - start];
        //printf("%ld(%ld) ", z[i], index[i]);
    }
    //printf("\n");
    //printf("end compare\n");
    free(pntemp);
    return;
}
void Merge2(double *pn, long int *z, long int start, long int last)
{
    if (start >= last)
        return;

    long int mid = (long int)((start + last) / (long int)2);

    while ((mid != start) && (z[mid] == z[mid - (long int)1])) // not to cut at the half of same z
        mid -= (long int)1;
    if (mid == start)
    {
        mid = (long int)((start + last) / (long int)2);
        while ((mid != last) && (z[mid] == z[mid + (long int)1]))
        {
            mid += (long int)1;
        }
        if (mid == last) // sort pn
        {
            pure_Merge(pn, start, last);
            return;
        }
    }
    else
        mid -= (long int)1;
    Merge2(pn, z, start, mid);
    Merge2(pn, z, mid + (long int)1, last);
    Compare2(pn, start, mid, last);
    return;
}
int main()
{
    long int N;
    scanf("%ld %lf %lf %lf", &N, &a, &b, &c);
    double p[N];
    //double pn[N];
    long int z[N];
    long int index[N];
    //std::vector<long int> z(N);
    //std::vector<long int> index(N);

    for (long int i = (long int)0; i < N; ++i)
    {
        scanf("%lf %ld", &p[i], &z[i]);
        //pn[i] = (b / a) * p[i] + c / a;
        index[i] = i;
    }
    Merge(z, index, (long int)0, N - (long int)1);
    //std::sort(index, index + N, [&](long int n1, long int n2)
    //          { return z[n1] < z[n2]; });
    /*
    for (int i = 0; i < N; ++i)
    {
        printf("%ld(%ld) ", z[i], index[i]);
    }
    printf("\n");
    */

    //long int n = 0;
    //std::generate(std::begin(index), std::end(index), [&]
    //              { return n++; });
    double pnnew[N];
    for (long int i = (long int)0; i < N; ++i)
        pnnew[i] = p[index[i]];

    Merge2(pnnew, z, 0, N - (long int)1);

    printf("%ld", score);

    return 0;
}