#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <functional>
int N;
long long int pair;
void Compare(std::vector<int> &z, std::vector<int> &index, int start, int mid, int last)
{
    // printf("compare\n");
    // int *ztemp = (int *)malloc((last - start + 1) * sizeof(int));
    // int *idtemp = (int *)malloc((last - start + 1) * sizeof(int));
    std::vector<int> ztemp(last - start + 1);
    std::vector<int> idtemp(last - start + 1);
    int pt1 = start;
    int pt2 = mid + 1;
    int temp_index = 0;

    while (1)
    {
        if (z[pt1] <= z[pt2])
        {
            ztemp[temp_index] = z[pt1];
            idtemp[temp_index] = index[pt1];
            pt1 += 1;
        }
        else
        {
            ztemp[temp_index] = z[pt2];
            idtemp[temp_index] = index[pt2];
            pt2 += 1;
        }
        temp_index += 1;

        if (pt1 > mid)
        {
            while (pt2 <= last)
            {
                ztemp[temp_index] = z[pt2];
                idtemp[temp_index] = index[pt2];
                pt2 += 1;
                temp_index += 1;
            }
            break;
        }
        else if (pt2 > last)
        {
            while (pt1 <= mid)
            {
                ztemp[temp_index] = z[pt1];
                idtemp[temp_index] = index[pt1];
                pt1 += 1;
                temp_index += 1;
            }
            break;
        }
    }

    for (int i = start; i <= last; ++i)
    {
        z[i] = ztemp[i - start];
        index[i] = idtemp[i - start];
        // printf("%d(%d) ", z[i], index[i]);
    }
    // printf("\n");
    // printf("end compare\n");
    // free(ztemp);
    // free(idtemp);
    std::vector<int>().swap(ztemp);
    std::vector<int>().swap(idtemp);
    return;
}
void Merge(std::vector<int> &z, std::vector<int> &index, int start, int last)
{
    // printf("merge\n");
    if (start >= last)
        return;
    int mid = (start + last) / 2;
    Merge(z, index, start, mid);
    Merge(z, index, mid + 1, last);
    Compare(z, index, start, mid, last);
    // printf("end merge\n");
    return;
}

void Pair(std::vector<int> &nx, std::vector<int> &ny, int start, int mid, int last)
{

    std::vector<int>::iterator lower, upper;
    std::vector<int> nx_l;
    std::vector<int> ny_l;
    std::vector<int> nx_r;
    std::vector<int> ny_r;
    int left = mid;
    ny_l.push_back(N + 1); // need to be large->no upper bound
    nx_l.push_back(N + 1);
    ny_r.push_back(0); // no use
    nx_r.push_back(0);
    // printf("Up\n");
    for (int i = last; i >= (mid + 1); --i) // up
    {
        while (ny[i] < ny[left] && left >= start) // insert left element
        {
            // printf("Compair:(%d,%d)!\n", nx[left], ny[left]);
            while (nx_l.back() < nx[left]) // insert left element to the correct place
            {
                nx_l.pop_back();
                ny_l.pop_back();
            }

            lower = std::lower_bound(ny_r.begin() + 1, ny_r.end(), ny[left], std::greater<int>()) - 1;
            upper = std::lower_bound(ny_r.begin() + 1, ny_r.end(), ny_l.back(), std::greater<int>());
            // printf("lower = %d, upper = %d\n", ny[left], ny_l.back());
            // printf("lower = %d, upper = %d\n", ny_r[lower - ny_r.begin()], ny_r[(upper - ny_r.begin())]);
            if ((ny_r.end() - ny_r.begin()) > 1)
            {
                if ((upper != ny_r.end()) && ((lower - ny_r.begin()) != 0)) // not found
                {
                    if ((ny_r[lower - ny_r.begin()] > ny[left]))
                    {
                        pair += lower - upper + 1;
                        // printf("(%d,%d), add: %d\n", nx[left], ny[left], upper - lower + 1);
                    }
                }
                // else
                //     printf("(%d,%d), add: 0(not found)\n", nx[left], ny[left]);
            }
            nx_l.push_back(nx[left]);
            ny_l.push_back(ny[left]);
            left -= 1;
        }
        // insert the right element
        while (nx_r.back() > nx[i]) // insert the right element to the correct place
        {
            nx_r.pop_back();
            ny_r.pop_back();
        }
        nx_r.push_back(nx[i]);
        ny_r.push_back(ny[i]);

        // for (int j = 1; j < (nx_r.end() - nx_r.begin()); ++j)
        //     printf("(%d, %d) ", nx_r[j], ny_r[j]);
        // printf("\n");
    }

    while (left >= start) // insert the remaining left element
    {
        // printf("Compair:(%d,%d)!\n", nx[left], ny[left]);
        while (nx_l.back() < nx[left]) // insert to the correct place
        {
            nx_l.pop_back();
            ny_l.pop_back();
        }
        lower = std::lower_bound(ny_r.begin() + 1, ny_r.end(), ny[left], std::greater<int>()) - 1;
        upper = std::lower_bound(ny_r.begin() + 1, ny_r.end(), ny_l.back(), std::greater<int>());
        // printf("lower = %d, upper = %d\n", ny[left], ny_l.back());
        // printf("lower = %d, upper = %d\n", ny_r[lower - ny_r.begin()], ny_r[(upper - ny_r.begin())]);
        if ((ny_r.end() - ny_r.begin()) > 1)
        {
            if ((upper != ny_r.end()) && ((lower - ny_r.begin()) != 0)) // not found
            {
                if (ny_r[lower - ny_r.begin()] > ny[left])
                {
                    pair += lower - upper + 1;
                    // printf("(%d,%d), add: %d\n", nx[left], ny[left], upper - lower + 1);
                }
            }
            // else
            //     printf("(%d,%d), add: 0(not found)\n", nx[left], ny[left]);
        }
        nx_l.push_back(nx[left]);
        ny_l.push_back(ny[left]);
        left -= 1;
    }

    std::vector<int>().swap(nx_l);
    std::vector<int>().swap(ny_l);
    std::vector<int>().swap(nx_r);
    std::vector<int>().swap(nx_r);
    ///////// down ////////////
    std::vector<int> dnx_l;
    std::vector<int> dny_l;
    std::vector<int> dnx_r;
    std::vector<int> dny_r;
    left = start;
    dny_l.push_back(0); // need to be small-> no lower bound
    dnx_l.push_back(N + 1);
    dny_r.push_back(0); // no use
    dnx_r.push_back(0);
    // printf("Down:\n");
    for (int i = mid + 1; i <= last; ++i) // down
    {
        while (ny[i] > ny[left] && left <= mid) // insert left stack
        {
            while (dnx_l.back() < nx[left]) // insert to the correct place
            {
                dnx_l.pop_back();
                dny_l.pop_back();
            }
            lower = std::lower_bound(dny_r.begin() + 1, dny_r.end(), dny_l.back());
            upper = std::lower_bound(dny_r.begin() + 1, dny_r.end(), ny[left]) - 1;
            // printf("lower = %d, upper = %d\n", dny_l.back(), ny[left]);
            // printf("lower = %d, upper = %d\n", lower - dny_r.begin(), upper - dny_r.begin());
            // printf("lower = %d, upper = %d\n", dny_r[(lower - dny_r.begin())], dny_r[upper - dny_r.begin()]);
            if ((dny_r.end() - dny_r.begin()) > 1)
            {
                if (((lower != dny_r.end()) && (upper - dny_r.begin()) != 0)) // not found
                {
                    if (dny_r[upper - dny_r.begin()] < ny[left])
                    {
                        pair += upper - lower + 1;
                        // printf("(%d,%d), add: %d\n", nx[left], ny[left], upper - lower + 1);
                    }
                }
                // else
                //     printf("(%d,%d), add: 0(upper not found)\n", nx[left], ny[left]);
            }
            dnx_l.push_back(nx[left]);
            dny_l.push_back(ny[left]);
            left += 1;
        }
        // insert right stack
        while (dnx_r.back() > nx[i]) // insert to the correct place
        {
            dnx_r.pop_back();
            dny_r.pop_back();
        }
        dnx_r.push_back(nx[i]);
        dny_r.push_back(ny[i]);
        // for (int j = 1; j < (dnx_r.end() - dnx_r.begin()); ++j)
        //     printf("(%d, %d) ", dnx_r[j], dny_r[j]);
        // printf("\n");
    }

    while (left <= mid) // insert the remaining left element
    {
        while (dnx_l.back() < nx[left]) // insert to the correct place
        {
            dnx_l.pop_back();
            dny_l.pop_back();
        }
        lower = std::lower_bound(dny_r.begin() + 1, dny_r.end(), dny_l.back());
        upper = std::lower_bound(dny_r.begin() + 1, dny_r.end(), ny[left]) - 1;
        // printf("lower = %d, upper = %d\n", dny_l.back(), ny[left]);
        // printf("lower = %d, upper = %d\n", lower - dny_r.begin(), upper - dny_r.begin());
        // printf("lower = %d, upper = %d\n", dny_r[(lower - dny_r.begin())], dny_r[upper - dny_r.begin()]);
        if ((dny_r.end() - dny_r.begin()) > 1)
        {
            if (((lower != dny_r.end()) && (upper - dny_r.begin()) != 0)) // not found
            {
                if (dny_r[upper - dny_r.begin()] < ny[left])
                {
                    pair += upper - lower + 1;
                    // printf("(%d,%d), add: %d\n", nx[left], ny[left], upper - lower + 1);
                }
            }
        }
        dnx_l.push_back(nx[left]);
        dny_l.push_back(ny[left]);
        left += 1;
    }
    std::vector<int>().swap(dnx_l);
    std::vector<int>().swap(dny_l);
    std::vector<int>().swap(dnx_r);
    std::vector<int>().swap(dnx_r);
}

void Merge2(std::vector<int> &nx, std::vector<int> &ny, int start, int last)
{
    // printf("merge\n");
    if (start == last)
        return;

    int mid = (start + last) / 2;
    Merge2(nx, ny, start, mid);
    Merge2(nx, ny, mid + 1, last);
    Pair(nx, ny, start, mid, last);
    Compare(ny, nx, start, mid, last);
    // printf("end merge\n");
    return;
}
int main()
{
    scanf("%ld", &N);
    std::vector<int> x(N);
    std::vector<int> y(N);

    for (int i = 0; i < N; ++i)
        scanf("%d %d", &x[i], &y[i]);

    Merge(x, y, 0, N - 1);
    // for (int i = 0; i < N; ++i)
    //     printf("%d %d\n", x[i], y[i]);

    Merge2(x, y, 0, N - 1);
    printf("%lld", pair);

    return 0;
}