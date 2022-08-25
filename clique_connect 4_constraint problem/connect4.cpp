#include "connect4.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>

// The columns are numbered from 0 to 6
int depth = 4;
std::vector<std::vector<int>> boardg(6, std::vector<int>(7, 0));
struct Ans
{
    int score;
    int column;
};
int Score(std::vector<std::vector<int>> &board)
{
    // row
    int score = 0;
    int count[3];
    count[1] = 0;
    count[2] = 0;
    for (int i = 0; i < 6; ++i)
    {
        count[1] = 0;
        count[2] = 0;
        count[board[i][0]] = 1;
        for (int j = 1; j < 7; ++j)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j] == board[i][j - 1])
                {
                    count[board[i][j]] += 1;
                    if (board[i][j] == 1)
                    {
                        if ((count[1] == 2) && (j < 5) && (board[i][j + 1] != 2) && (board[i][j + 2] != 2))
                            score++;
                        if ((count[1] == 3) && (j < 6) && (board[i][j + 1] != 2))
                            score += 10;
                        if (count[1] == 4)
                            score += 100;
                    }
                    else
                    {
                        if ((count[2] == 2) && (j < 5) && (board[i][j + 1] != 1) && (board[i][j + 2] != 1))
                            score -= 1;
                        /*
                    if (j + 3 < 7)
                    {
                        if ((board[i][j + 1] != 1) && !((i - 1 >= 0) && (board[i - 1][j + 1] == 0)) && (board[i][j + 2] == 2) && (board[i][j + 3] == 2))
                            score -= 100;
                        else if ((board[i][j + 1] == 2) && (board[i][j + 2] != 1) && !((i - 1 >= 0) && (board[i - 1][j + 2] == 0)) && (board[i][j + 3] == 2))
                            score -= 100;
                        else if ((board[i][j + 1] == 2) && (board[i][j + 2] == 2) && (board[i][j + 3] != 1) && !((i - 1 >= 0) && (board[i - 1][j + 3] == 0)))
                            score -= 100;
                    }
                    else
                    */
                        if ((count[2] == 3) && (j < 6) && (board[i][j + 1] != 1))
                            score -= 100;
                        if (count[2] == 4)
                            score -= 100;
                    }
                }
                else
                {
                    count[board[i][j]] = 1;
                    count[board[i][j - 1]] = 0;
                }
            }
        }
    }
    // colume
    for (int j = 0; j < 7; ++j)
    {
        count[1] = 0;
        count[2] = 0;
        count[board[0][j]] = 1;
        for (int i = 1; i < 6; ++i)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j] == board[i - 1][j])
                {
                    count[board[i][j]] += 1;
                    if (board[i][j] == 1)
                    {
                        if ((count[1] == 2) && (i < 4) && (board[i + 1][j] != 2) && (board[i + 2][j] != 2))
                            score++;
                        if ((count[1] == 3) && (i < 5) && (board[i + 1][j] != 2))
                            score += 10;
                        if (count[1] == 4)
                            score += 100;
                    }
                    else
                    {
                        if ((count[2] == 2) && (i < 4) && (board[i + 1][j] != 1) && (board[i + 2][j] != 1))
                            score -= 1;
                        if ((count[2] == 3) && (i < 5) && (board[i + 1][j] != 1))
                            score -= 100;
                        if (count[2] == 4)
                            score -= 100;
                    }
                }
                else
                {
                    count[board[i][j]] = 1;
                    count[board[i - 1][j]] = 0;
                }
            }
        }
    }
    // tile right
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if ((board[i][j] == 1) && (board[i][j] == board[i + 1][j + 1])) // 2 same
            {
                score++;
                if (board[i + 2][j + 2] == 1) // 3 same
                {
                    score += 10;
                    if (board[i + 3][j + 3] == 1)
                        score = score + 100;
                }
            }

            if ((board[i][j] == 2) && (board[i][j] == board[i + 1][j + 1])) // 2 same
            {
                score -= 1;
                if (board[i + 2][j + 2] == 2) // 3 same
                {
                    score -= 100;
                    if (board[i + 3][j + 3] == 2)
                        score = score - 100;
                }
            }
        }
    }
    // tile left
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 6; j > 2; --j)
        {
            if ((board[i][j] == 1) && (board[i][j] == board[i + 1][j - 1]))
            {
                score++;
                if (board[i + 2][j - 2] == 1)
                {
                    score += 10;
                    if (board[i + 3][j - 3] == 1)
                        score = score + 100;
                }
            }

            if ((board[i][j] == 2) && (board[i][j] == board[i + 1][j - 1]))
            {
                score -= 1;
                if (board[i + 2][j - 2] == 2)
                {
                    score -= 100;
                    if (board[i + 3][j - 3] == 2)
                        score = score - 100;
                }
            }
        }
    }
    return score;
}
void Copy(std::vector<std::vector<int>> &nb, std::vector<std::vector<int>> &ob)
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
            nb[i][j] = ob[i][j];
    }
}
Ans minimax(int d, std::vector<std::vector<int>> &board, int alpha, int beta)
{
    struct Ans ans;
    if (d == 5)
    {
        ans.score = Score(board);
        return ans;
    }
    std::vector<std::vector<std::vector<int>>> B;
    int scoretmp = 0, column = -1;
    int mm;
    if (d % 2 == 1) // get max
    {
        mm = std::numeric_limits<int>::min();
        for (int j = 0; j < 7; ++j)
        {
            for (int i = 0; i < 6; ++i)
            {
                if (board[i][j] == 0) // valid
                {
                    B.push_back(std::vector<std::vector<int>>(6, std::vector<int>(7, 0)));
                    Copy(B[B.size() - 1], board);
                    B[B.size() - 1][i][j] = 1;
                    struct Ans tt = minimax(d + 1, B[B.size() - 1], alpha, beta);
                    scoretmp = tt.score;
                    if (tt.column == -1)
                        scoretmp = Score(B[B.size() - 1]);
                    if (scoretmp > mm)
                    {
                        mm = scoretmp;
                        column = j;
                    }
                    if (alpha < scoretmp)
                        alpha = scoretmp;

                    if (alpha >= beta)
                    {
                        ans.score = mm;
                        ans.column = column;
                        return ans;
                    }

                    break;
                }
            }
        }
    }
    else
    {
        mm = std::numeric_limits<int>::max();
        for (int j = 0; j < 7; ++j)
        {
            for (int i = 0; i < 6; ++i)
            {
                if (board[i][j] == 0) // valid
                {
                    B.push_back(std::vector<std::vector<int>>(6, std::vector<int>(7, 0)));
                    Copy(B[B.size() - 1], board);
                    B[B.size() - 1][i][j] = 2;
                    struct Ans tt = minimax(d + 1, B[B.size() - 1], alpha, beta);
                    scoretmp = tt.score;
                    if (tt.column == -1)
                        scoretmp = Score(B[B.size() - 1]);
                    if (scoretmp < mm)
                    {
                        mm = scoretmp;
                        column = j;
                    }
                    if (beta > scoretmp)
                        beta = scoretmp;

                    if (alpha >= beta)
                    {
                        ans.score = mm;
                        ans.column = column;
                        return ans;
                    }

                    break;
                }
            }
        }
    }
    ans.score = mm;
    ans.column = column;
    return ans;
}
/*
int simple()
{
    int mm = std::numeric_limits<int>::min();
    int mincol = -1, minrow = -1;
    int temp;
    for (int j = 0; j < 7; ++j)
    {
        for (int i = 0; i < 6; ++i)
        {
            if (board[0][i][j] == 0) // valid
            {
                board[0][i][j] = 1;
                temp = Score(0);
                board[0][i][j] = 0;
                if (temp > mm)
                {
                    mm = temp;
                    minrow = i;
                    mincol = j;
                }
                break;
            }
        }
    }
    // printf("GET SCORE: %d\n", mm);
    board[0][minrow][mincol] = 1;
    return mincol;
}
*/
int decide(int yp_move)
{
    if (yp_move == -1)
    {
        // A new game starts
        // TODO: Please remember to reset everything here (if needed)
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 7; ++j)
                boardg[i][j] = 0;
        }
    }
    else
    {
        // YP placed his piece at column `yp_move`
        for (int i = 0; i < 6; ++i)
        {
            if (boardg[i][yp_move] == 0)
            {
                boardg[i][yp_move] = 2;
                break;
            }
        }
    }
    struct Ans ans = minimax(1, boardg, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    int retcol = ans.column;
    for (int i = 0; i < 6; ++i)
    {
        if (boardg[i][retcol] == 0)
        {
            boardg[i][retcol] = 1;
            break;
        }
    }
    // printf("GET SCORE1: %d\n", Score(boardg));
    // printf("GET SCORE2: %d\n", ans.score);
    //  printf("GET SCORE2: %d\n", Score(boardg));
    return retcol; // always place at the rightmost column
}
