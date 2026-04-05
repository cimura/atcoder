#include <iostream>
#include <queue>

using namespace std;
#define SIZE 1000

// bfsを使おう

int main() {
  int h, w;
  cin >> h >> w;

  int count = 0;
  vector<string> map(h);
  vector<vector<bool>> visited(h, vector<bool>(w, false));
  for (int i = 0; i < h; ++i) cin >> map[i];

  int dx[] = { 0, 0, 1, -1 };
  int dy[] = { -1, 1, 0, 0 };

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      if (map[y][x] == '.' && !visited[y][x] && x != 0 && x != w - 1 && y != 0 && y != h - 1) {
        cout << "x: " << x << ", y: " << y << endl;
        count++;
        queue<pair<int, int>> q;
        q.push({ y, x });
        visited[y][x] = true;

        while (!q.empty()) {
          pair<int, int> p = q.front();
          q.pop();

          for (int i = 0; i < 4; ++i) {
            int ny = p.first + dy[i];
            int nx = p.second + dx[i];

            if (nx >= 0 && nx < w && ny >= 0 && ny < h && !visited[ny][nx] && map[ny][nx] == '.') {
              visited[ny][nx] = true;
              q.push({ny, nx});
            }
          }
        }
      }

    }
  }
  cout << count << endl;
}
