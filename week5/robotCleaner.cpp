#include <iostream>
#include <vector>
using namespace std;

typedef enum Dir_t {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Dir_t;

int main(int argc, char** argv) {
    int n, m, i, j;
    int cnt = 0;
    vector<vector<int>> room;
    Dir_t dir;
    int d;
    int di[4] = { -1, 0, 1, 0 };
    int dj[4] = { 0, 1, 0, -1 };
    
    cin >> n >> m;
    room = vector<vector<int>>(n+2, vector<int>(m+2, 0));
    cin >> i >> j >> d;
    i += 1; j += 1;
    for(int i = 1 ; i <= n ; i++) {
        for(int j = 1 ; j <= m ; j++) {
            cin >> room[i][j];
        }
    }
    
    // 테두리 부분 벽으로 설정하기
    for(int i = 0 ; i <= n+1 ; i++) {
        room[i][0]   = 1;
        room[i][m+1] = 1;
    }
    for(int j = 0 ; j <= m+1 ; j++) {
        room[0][j]   = 1;
        room[n+1][j] = 1;
    }
    
    while(room[i][j] != 1) {
        if(room[i][j] == 0) {
            room[i][j] = -1;
            cnt += 1;
        }
        
        for(int k = 0 ; k < 4 ; k++) {
            d = (d == 0) ? 3 : d-1;
            
            if(room[i+di[d]][j+dj[d]] == 0) {
                i += di[d]; j += dj[d];
                break;    
            }
            
            if(k == 3) {    // 모든 방향이 벽이거나 청소함
//                d = (d < 2) ? 3-d : d-2;    // 뒤쪽 방향으로 설정
                i -= di[d]; j -= dj[d];
//                d = (d < 2) ? 3-d : d-2;    // 원래 방향 유지
            }
        }
    }
    
    cout << cnt;
    
    return 0;
}
