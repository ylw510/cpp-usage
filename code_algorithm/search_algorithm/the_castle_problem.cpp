#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int row_num,col_num;

using TMap = vector<vector<int>>;
using Visit = vector<vector<bool>>;

TMap t_map;
Visit visit;
int max_area;
int room_cnt = 0;

int do_bfs(int start_x, int start_y)
{
        using Cell = std::pair<int, int>;
        queue<Cell> cell_queue;
        vector<int> coordinate_x = {0, -1, 0, 1};
        vector<int> coordinate_y = {-1, 0, 1, 0};


        cell_queue.push({start_x, start_y});
        visit[start_x][start_y] = true;
        int area = 0;

        while(!cell_queue.empty())
        {
                Cell cell = cell_queue.front();
                cell_queue.pop();
                area ++;

                //遍历东南西北4个方向
                for (int i = 0; i < 4; i++)
                {
                        int point_x = cell.first + coordinate_x[i];
                        int point_y = cell.second + coordinate_y[i];
                        if (point_x < 0 || point_x >= row_num || point_y < 0 || point_y >= col_num) // 是否越界
                                continue;
                        if (visit[point_x][point_y]) //[point_x, point_y] 该点已经被访问过
                                continue;
                        if (t_map[cell.first][cell.second] >> i & 1) // 查看 >> i 方向是否有墙
                                continue;
                        cell_queue.push({point_x, point_y});
                        visit[point_x][point_y] = true;
                }
        }
        return area;
}

int main()
{
        cin >> row_num >> col_num;
        t_map.resize(row_num, vector<int>(col_num));
        visit.resize(row_num, vector<bool>(col_num, false));

        for (int i = 0; i < row_num; i++)
        {
                for (int j = 0; j < col_num; j++)
                {
                        cin >> t_map[i][j];
                }
        }


        for (int i = 0; i < t_map.size(); ++i)
        {
                for (int j = 0; j < t_map[0].size(); j++)
                {
                        if (!visit[i][j])
                        {
                                max_area = std::max(max_area, do_bfs(i, j));
                                room_cnt++;
                        }
                }
        }


        cout << room_cnt << std::endl << max_area;
}

