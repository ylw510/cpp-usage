#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using Pond = vector<vector<char>>;
using Visit = vector<vector<bool>>;

int row_num = 0, col_num = 0;

void do_bfs(int start_x, int start_y, Pond &pond, Visit &visit) {
  using cell = pair<int, int>;
  queue<cell> cell_queue;
  cell_queue.push({start_x, start_y});
  visit[start_x][start_y] = true;

  while (!cell_queue.empty()) {
    cell c = cell_queue.front();
    cell_queue.pop();

    for (int i = c.first - 1; i <= c.first + 1; i++) {
      for (int j = c.second - 1; j <= c.second + 1; j++) {
        if (i == c.first && j == c.second)
          continue;
        if (i < 0 || i >= row_num || j < 0 || j >= col_num)
          continue;
        if (pond[i][j] != 'W' || visit[i][j])
          continue;

        cell_queue.push({i, j});
        visit[i][j] = true;
      }
    }
  }
}

int main() {
  int puddle_cnt = 0;

  cin >> row_num >> col_num;

  Pond pond(row_num, vector<char>(col_num));
  Visit visit(row_num, vector<bool>(col_num, false));

  for (int i = 0; i < row_num; i++) {
    for (int j = 0; j < col_num; j++) {
      cin >> pond[i][j];
    }
  }

  for (int i = 0; i < row_num; i++) {
    for (int j = 0; j < col_num; j++) {
      if (pond[i][j] == 'W' && !visit[i][j]) {
        do_bfs(i, j, pond, visit);
        puddle_cnt++;
      }
    }
  }

  cout << puddle_cnt << endl;
}

