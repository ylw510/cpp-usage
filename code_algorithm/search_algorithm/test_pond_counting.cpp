#include <iostream>
#include <vector>
#include <queue>
#include <random>

/*
root@ubantu64:~/cpp-usage/code_algorithm# ./a.out
10 10 0.5
.WW...W.WW
.WWW.....W
..W.W.W..W
.........W
WW.WW.....
W.WWWW.WWW
WW..W.....
WW.WW...W.
.WW.WWW.WW
W.WWWWWW.W
6
*/

using namespace std;

using Pond = vector<vector<char>>;
using Visit = vector<vector<bool>>;

int row_num = 0, col_num = 0;

/* 8 连通 BFS */
void do_bfs(int start_x, int start_y, Pond &pond, Visit &visit)
{
    queue<pair<int, int>> q;
    q.push({start_x, start_y});
    visit[start_x][start_y] = true;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        for (int i = x - 1; i <= x + 1; i++)
        {
            for (int j = y - 1; j <= y + 1; j++)
            {
                if (i < 0 || i >= row_num || j < 0 || j >= col_num)
                    continue;
                if (pond[i][j] != 'W' || visit[i][j])
                    continue;

                visit[i][j] = true;
                q.push({i, j});
            }
        }
    }
}

/* 随机生成 pond（水率可控） */
Pond generate_random_pond(int n, int m, double water_ratio)
{
    Pond pond(n, vector<char>(m, '.'));

    mt19937 gen(12345); // 固定种子，方便复现
    uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            pond[i][j] = (dist(gen) < water_ratio) ? 'W' : '.';

    return pond;
}

int main()
{
    cin >> row_num >> col_num;

    /* ===== 模式控制 =====
       true  -> 随机生成（调试）
       false -> 从输入读入（OJ）
    */
    bool use_random = true;

    Pond pond;
    Visit visit(row_num, vector<bool>(col_num, false));

    if (use_random)
    {
        double water_ratio;
        cin >> water_ratio;   // 例如：0.3 表示 30% 是水

        pond = generate_random_pond(row_num, col_num, water_ratio);
    }
    else
    {
        pond.assign(row_num, vector<char>(col_num));
        for (int i = 0; i < row_num; i++)
            for (int j = 0; j < col_num; j++)
                cin >> pond[i][j];
    }

    /* 打印 pond（调试用，可删） */
    for (int i = 0; i < row_num; i++)
    {
        for (int j = 0; j < col_num; j++)
            cout << pond[i][j];
        cout << '\n';
    }

    int puddle_cnt = 0;
    for (int i = 0; i < row_num; i++)
    {
        for (int j = 0; j < col_num; j++)
        {
            if (pond[i][j] == 'W' && !visit[i][j])
            {
                do_bfs(i, j, pond, visit);
                puddle_cnt++;
            }
        }
    }

    cout << puddle_cnt << '\n';
    return 0;
}

