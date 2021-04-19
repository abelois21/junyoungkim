#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

int whole_space, fixed_wall;
vector<pair<int, int>> virus;

string pair2Str(pair<int, int> p) {
    string str;
    str = to_string(p.first) + "#" + to_string(p.second);
    return str;    
} 

int safeSpaces(const vector<vector<int>>& v, const vector<pair<int, int>>& selected_wall) {
    int row, col;
    queue<pair<int, int>> waits;
    unordered_map<string, bool> isVisited;
    
    // 병균의 주변 부위 큐에 넣기
//    for(auto it = virus.begin() ; it != virus.end() ; it++)
//        waits.push(*it);

    for(const auto p : virus)
	waits.push(p);
    
    // 차단벽 위치 설정
//    for(auto it = selected_wall.begin() ; it != selected_wall.end() ; it++) 
//        isVisited[pair2Str(*it)] = 1;

    for(const auto p : selected_wall)
	isVisited[pair2Str(p)] = 1;
    
    while(!waits.empty()) {
        row = waits.front().first;
        col = waits.front().second;
        waits.pop();
        isVisited[pair2Str(pair<int, int>(row, col))] = 1;
        
        row -= 1;
        if(v[row][col] != 1 && !isVisited[pair2Str(pair<int, int>(row, col))]) 
            waits.push(pair<int, int>(row, col));
        row += 2;
        if(v[row][col] != 1 && !isVisited[pair2Str(pair<int, int>(row, col))]) 
            waits.push(pair<int, int>(row, col));
        row -= 1;
        col -= 1;
        if(v[row][col] != 1 && !isVisited[pair2Str(pair<int, int>(row, col))]) 
            waits.push(pair<int, int>(row, col));
        col += 2;
        if(v[row][col] != 1 && !isVisited[pair2Str(pair<int, int>(row, col))]) 
            waits.push(pair<int, int>(row, col));
    }
    
    return whole_space - fixed_wall - isVisited.size();
}

int main(int argc, char** argv) {
    int n, m, empty_spaces = 0, tmp, max = 0;
    vector<int> cbn_code;
    vector<vector<int>> board;
    unordered_map<int, pair<int, int>> spaces;
    
    cin >> n >> m;
    whole_space = n * m;
    board = vector<vector<int>>(n+2, vector<int>(m+2, 0));
    
    for(int i = 1 ; i <= n ; i++) { 
        for(int j = 1 ; j <= m ; j++) {
            cin >> tmp;
            board[i][j] = tmp;
            if(tmp == 0) {
                spaces[empty_spaces++] = pair<int, int>(i, j);
            } else if(tmp == 1) {
                fixed_wall += 1;
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
    
    // 조합을 위한 세팅
    cbn_code = vector<int>(empty_spaces, 0);
    for(int i = empty_spaces - 1 ; i >= empty_spaces -  3 ; i--) 
        cbn_code[i] = 1;
    
    do {
        vector<pair<int, int>> selected_wall(3, pair<int, int>(0, 0));
        int cnt = 0;
        
        for(int i = 0 ; i < empty_spaces ; i++) {
            if(cbn_code[i]) {
                selected_wall[cnt++] = spaces[i];
            }
            if(cnt == 3) break;
        }
        
        tmp = safeSpaces(board, selected_wall);
        if(tmp > max) max = tmp;
    } while(std::next_permutation(cbn_code.begin(), cbn_code.end()));
    
    cout << max;
    
    return 0;
}
