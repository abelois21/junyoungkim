#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
using namespace std;

typedef enum Dir_t{
    RIGHT,
    DOWN,
    LEFT,
    UP
} Dir_t;

int main(int argc, char** argv) {
    int n, n_apple, n_turn, tmp = 0, cnt = 0, result = 0;
    pair<int, int> head, tail;
    vector<pair<int ,Dir_t>> idc;
    queue<pair<int, int>> warm;
    clock_t start = clock();
    
    head.first = head.second = tail.first = tail.second = 1;
    
    cin >> n >> n_apple;
    vector<vector<int>> board(n+2, vector<int>(n+2, 0));
    for(size_t i = 0 ; i < board.size() ; i++) {
        board[0][i]   = -1;
        board[n+1][i] = -1;
        board[i][0]   = -1;
        board[i][n+1] = -1;        
    }
    
    for(int i = 0 ; i < n_apple ; i++) {
        int row, col;
        cin >> row >> col;
        board[row][col] = 1;
    }
    cin >> n_turn;
    

    // idc에는 앞으로 몇 초 동안 어떤 방향으로 진행하는 지에 대한 정보
    char ch;
    Dir_t dir = RIGHT;
    for(int i = 0 ; i < n_turn ; i++) {
        int t;
        cin >> t;
        
        idc.push_back(pair<int, Dir_t>(t - tmp, dir));
        tmp = t;
        
        cin >> ch;
        if(ch == 'L') {
            dir = ((int)dir == 0) ? (Dir_t)3 : (Dir_t)((int)dir-1);
        }
        else if(ch == 'D') {
            dir = ((int)dir == 3) ? (Dir_t)0 : (Dir_t)((int)dir+1);
        }
    }
    idc.push_back(pair<int, Dir_t>(101, dir));
  
    // 큐를 사용하여 tail의 위치 정보를 갱신
    // 부딪히는지 여부는 head로만 
    int idx = -1;
    board[1][1] = -1;
    warm.push(pair<int, int>(1, 1));
    while(++idx < idc.size()) {
        // 명령 갱신
        dir   = idc[idx].second;
        
        for(int i = idc[idx].first ; i > 0 ; i--) {
            cnt += 1;
            
            switch(dir) {
            case RIGHT:
                head.second += 1;
                break;
            case DOWN:
                head.first  += 1;
                break;
            case LEFT:
                head.second -= 1;
                break;
            case UP:
                head.first  -= 1;
                break;
            }
            
            // 사과를 먹으면 꼬리에 대한 갱신 없이 넘어감
            
            if(board[head.first][head.second] == -1) {    // 부딪힘
                result = cnt;
                break;
            } else if(board[head.first][head.second] == 0){    // 꼬리 움직임 반영하기
                pair<int, int> loc = warm.front();
                warm.pop();
                board[loc.first][loc.second] = 0;
            }
            // 머리 부분 위치 갱신하기
            board[head.first][head.second] = -1;
            warm.push(pair<int, int>(head.first, head.second));
        }
        
        if(result) break;
    }
    cout << result;

    return 0;
}
