#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    int N, L;
    int passed, cnt = 0;
    bool impossible = 0;;
    vector<vector<int>> board;
    vector<vector<int>> shouldCrossed;
    
    cin >> N >> L;
    board = vector<vector<int>>(N, vector<int>(N, 0));
    shouldCrossed = vector<vector<int>>(N, vector<int>(N, 0));
//    vector<vector<int>> board(N, vector<int>(N, 0));
//    vector<vector<int>> shouldCrossed(N, vector<int>(N, 0));
    for(int i = 0 ; i < N ; i++) 
        for(int j = 0 ; j < N ; j++) 
            cin >> board[i][j];
    
    // 가로 길 탐색
    for(int row = 0 ; row < N ; row++) {
        passed = board[row][0];
        for(int col = 0 ; col < N ; col++) {    
            if(passed == board[row][col]) {
                continue;
            } else if(passed - board[row][col] == 1) { 
                if(col+L <= N) {    
                    impossible = 1;
                    break;
                } 
                for(int k = col ; k < col+L ; k++) // 현재 위치포함 L개
                    shouldCrossed[row][k] += 1;
            } else if(passed - board[row][col] == -1) { 
                if(col-L >= 0) {
                    impossible = 1;
                    break;
                }
                for(int k = col-1 ; k >= col-L ; k--) // 현재 위치 미포함 L개
                    shouldCrossed[row][k] += 1;
            } else {    // 경사차이가 1 이상
                impossible = 1;
                break;
            }
            passed = board[row][col];    
        }
        
        if(impossible) {
            impossible = 0;
            continue;
        }
        
        for(int row = 0 ; row < N ; row++) {
            impossible = 0;
            for(int col = 0 ; col < N ; col++) {    // 경사로가 중복되어 설치되었는지 확인
                if(shouldCrossed[row][col] > 1) {
                    impossible = 1;
                    break;
                }
            }
            if(impossible) {
                impossible = 0;
                continue;
            }
            cnt += 1;
        }
    }
    
/*    // shouldCrossed clear
    for(int i = 0 ; i < N ; i++) 
        for(int j = 0 ; j < N ; j++) 
            shouldCrossed[i][j] = 0;
*/	    
/*   
    // 세로 길 탐색
    for(int col = 0 ; col < N ; col++) {
        passed = board[0][col];
        for(int row = 0 ; row < N ; row++) {    
            if(passed == board[row][col]) {
                continue;
            } else if(passed - board[row][col] == 1) { 
                if(row+L <= N) {    
                    impossible = 1;
                    break;
                } 
                for(int k = row ; k < row+L ; k++) // 현재 위치포함 L개
                    shouldCrossed[k][col] += 1;
            } else if(passed - board[row][col] == -1) { 
                if(row-L >= 0) {
                    impossible = 1;
                    break;
                }
                for(int k = row-1 ; k >= row-L ; k--) // 현재 위치 미포함 L개
                    shouldCrossed[k][col] += 1;
            } else {    // 경사차이가 1 이상
                impossible = 1;
                break;
            }
            passed = board[row][col];    
        }
        
        if(impossible) {
            impossible = 0;
            continue;
        }
        
        for(int col = 0 ; col < N ; col++) {
            impossible = 0;
            for(int row = 0 ; row < N ; row++) {    // 경사로가 중복되어 설치되었는지 확인
                if(shouldCrossed[row][col] > 1) {
                    impossible = 1;
                    break;
                }
            }
            if(impossible) {
                impossible = 0;
                continue;
            }
            cnt += 1;
        }
    }
*/    
    cout << cnt;
    return 0;
}
