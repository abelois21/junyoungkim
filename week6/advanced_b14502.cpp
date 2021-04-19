#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <time.h>
using namespace std;

int n, m, max_area;
vector<vector<int>> board;
vector<pair<int, int>> virus;
// const int di[4] = { -1, 0, 1, 0 };
// const int dj[4] = { 0, 1, 0, -1 };

void safeSpaces(vector<pair<int, int>>& selected_wall) {
    int row, col, cnt = 0;
    queue<pair<int, int>> waits;
    vector<vector<int>> v(board.begin(), board.end());
    
    // 병균의 주변 부위 큐에 넣기
    for(const auto p : virus)
	waits.push(p);
    
    // 차단벽 위치 설정
    for(const auto p : selected_wall)
	v[p.first][p.second] = 1;
    
    while(!waits.empty()) {
        row = waits.front().first;
        col = waits.front().second;
        waits.pop();
	v[row][col] = 1;
     
        row -= 1;
        if(v[row][col] != 1) 
            waits.push(pair<int, int>(row, col));
        row += 2;
        if(v[row][col] != 1) 
            waits.push(pair<int, int>(row, col));
        row -= 1;
        col -= 1;
        if(v[row][col] != 1) 
            waits.push(pair<int, int>(row, col));
        col += 2;
        if(v[row][col] != 1) 
            waits.push(pair<int, int>(row, col));    
    }

    for(auto i : v) 
	for(auto j : i) 
	    if(j == 0) cnt += 1;

    if(max_area < cnt) max_area = cnt;

    return;
}

int main(int argc, char** argv) {
    int empty_spaces = 0, tmp, max = 0;
    unordered_map<int, pair<int, int>> spaces;
    clock_t start = clock();
    
    cin >> n >> m;
    board = vector<vector<int>>(n+2, vector<int>(m+2, 0));
    
    for(int i = 1 ; i <= n ; i++) { 
        for(int j = 1 ; j <= m ; j++) {
            cin >> tmp;
            board[i][j] = tmp;
            if(tmp == 0) {
                spaces[empty_spaces++] = pair<int, int>(i, j);
            } else if(tmp == 2) {
                virus.push_back(pair<int, int>(i, j));
            }
        } 
    }
    
    // 보드 바깥 부분 설정
    for(int i = 0 ; i < m+2 ; i++) {
        board[0][i]   = 1;
        board[n+1][i] = 1;
    }
    for(int i = 0 ; i < n+2 ; i++) {
        board[i][0]   = 1;
        board[i][m+1] = 1;
    }
 
    vector<pair<int, int>> selected_wall(3, pair<int, int>(0, 0));
    for(int i = 0 ; i < empty_spaces-2 ; i++) {
	selected_wall[0] = spaces[i];
	for(int j = i+1 ; j < empty_spaces-1 ; j++) {
	    selected_wall[1] = spaces[j];
	    for(int k = j+1 ; k < empty_spaces ; k++) {
		selected_wall[2] = spaces[k];
		safeSpaces(selected_wall);
	    }
	}
    }
    
    cout << max_area << endl;
    cout << "time consuming: " << (double)(clock() - start) << "us \n";
    
    return 0;
}
