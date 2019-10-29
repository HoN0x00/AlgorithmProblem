#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main(void)
{
    int R, T, C;
    int dirx[] = {1, 0, -1, 0};
    int diry[] = {0, -1, 0, 1};
    int upArea[] = {2, 3, 0, 1};
    int downArea[] = {0, 3, 2, 1};

    cin >> R >> C >> T;

    pair<int **, int **> map;
    pair<int, int> airCon[2];

    map.first = new int *[R + 1];
    map.second = new int *[R + 1];

    for (int i = 0; i <= R; i++)
    {
        map.first[i] = new int[C + 1];
        map.second[i] = new int[C + 1];
        memset(map.second[i], 0, sizeof(int) * (C + 1));
    }

    int count = 0;
    for (int x = 1; x <= R; x++)
    {
        for (int y = 1; y <= C; y++)
        {
            cin >> map.first[x][y];

            if (map.first[x][y] == -1)
            {
                airCon[count].first = x;
                airCon[count].second = y;
                map.second[x][y] = -1;

                count++;
            }
        }
    }

    bool flag = true;
    int **cur = NULL;
    int **next = NULL;

    for (int t = 0; t < T; t++)
    {
        if (flag)
        {
            cur = map.first;
            next = map.second;
        }
        else
        {
            cur = map.second;
            next = map.first;
        }

        //확산
        for (int x = 1; x <= R; x++)
        {
            for (int y = 1; y <= C; y++)
            {
                if (cur[x][y] > 0)
                {
                    int seperSize = cur[x][y] / 5;

                    if (seperSize != 0)
                    {
                        for (int d = 0; d < 4; d++)
                        {
                            int nx = x + dirx[d];
                            int ny = y + diry[d];

                            if (nx < 1 || ny < 1 || nx > R || ny > C || next[nx][ny] == -1)
                            {
                                continue;
                            }
                            else
                            {
                                next[nx][ny] += seperSize;
                                cur[x][y] -= seperSize;
                            }
                        }
                    }

                    next[x][y] += cur[x][y];

                    cur[x][y] = 0;
                }
            }
        }

        //바람 UPAREA
        int curx = airCon[0].first + dirx[upArea[0]];
        int cury = airCon[0].second + diry[upArea[0]];

        next[curx][cury] = 0;

        for (int d = 0; d < 4; d++)
        {
            while (true)
            {
                int nx = curx + dirx[upArea[d]];
                int ny = cury + diry[upArea[d]];

                if (nx < 1 || ny < 1 || nx > airCon[0].first || ny > C)
                {
                    break;
                }
                else
                {
                    if (next[nx][ny] == -1)
                    {
                        next[curx][cury] = 0;
                        break;
                    }

                    next[curx][cury] = next[nx][ny];
                    curx = nx;
                    cury = ny;
                }
            }
        }

        //바람 DOWNAREA
        curx = airCon[1].first + dirx[downArea[0]];
        cury = airCon[1].second + diry[downArea[0]];

        next[curx][cury] = 0;

        for (int d = 0; d < 4; d++)
        {
            while (true)
            {
                int nx = curx + dirx[downArea[d]];
                int ny = cury + diry[downArea[d]];

                if (nx < airCon[1].first || ny < 1 || nx > R || ny > C)
                {
                    break;
                }
                else
                {
                    if (next[nx][ny] == -1)
                    {
                        next[curx][cury] = 0;
                        break;
                    }

                    next[curx][cury] = next[nx][ny];
                    curx = nx;
                    cury = ny;
                }
            }
        }

        flag = !flag;
    }

    int answer = 0;

    for (int x = 1; x <= R; x++)
    {
        for (int y = 1; y <= C; y++)
        {
            if (next[x][y] > 0)
            {
                answer += next[x][y];
            }
        }
    }

    cout << answer << endl;

    for (int i = 0; i <= R; i++)
    {
        delete[] map.first[i];
        delete[] map.second[i];
    }

    delete[] map.first;
    delete[] map.second;

    return 0;
}