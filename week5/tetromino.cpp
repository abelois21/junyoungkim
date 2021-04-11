#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#define MAX_MOVE 4
using namespace std;

// Backjoon 14500 tetromino
// 재귀로 돌아오는 것과 함수에서 처리하는 것의 속도 차이

vector<vector<int>> board;
vector<int> maximum_bound;
int n, m, g_max;

static bool greator(int a, int b) {
    return a > b;
}

void dfs(int n, int pre_sum, pair<int, int> next, pair<int, int> previous) {
    int cur_sum = pre_sum + board[next.first][next.second];
    if(n == MAX_MOVE) {
	if(cur_sum > g_max) g_max = cur_sum;
	return;
    }
    if(g_max >= cur_sum + maximum_bound[MAX_MOVE-n-1]) return;
    
    int i = next.first, j = next.second, tmp, max = 0;
    vector<int> v;
    
    if(i != 0 && !(i-1 == previous.first && j == previous.second)) {
        dfs(n+1, cur_sum, pair<int, int>(i-1, j), next);
	v.push_back(board[i-1][j]);
    }
    if(j != 0 && !(i == previous.first && j-1 == previous.second)) {
        dfs(n+1, cur_sum, pair<int, int>(i, j-1), next);
	v.push_back(board[i][j-1]);
    }
    if(i != n-1 && !(i+1 == previous.first && j == previous.second)) {
        dfs(n+1, cur_sum, pair<int, int>(i+1, j), next);
	v.push_back(board[i+1][j]);
    }
    if(j != m-1 && !(i == previous.first && j+1 == previous.second)) {
        dfs(n+1, cur_sum, pair<int, int>(i, j+1), next);
	v.push_back(board[i][j+1]);
    }

    if(v.size() >=  MAX_MOVE-n) {
	tmp = cur_sum;
    	sort(v.begin(), v.end(), greator);
    	for(int i = 0 ; i < MAX_MOVE-n ; i++) {
	    tmp += v[i];
	}
    	if(tmp > g_max) g_max = tmp;
    }

    return;
}

int main(int argc, char** argv) {
    int bound = 0, tmp;
    clock_t start = clock();
    maximum_bound = vector<int>(4, 0);
    
    cin >> n >> m;
    board = vector<vector<int>>(n+1, vector<int>(m+1, 0));
    for(int i = 0 ; i < n ; i++) { 
        for(int j = 0 ; j < m ; j++) {
            cin >> tmp;
            board[i][j] = tmp;    
            if(tmp > bound) {
                maximum_bound[3] = tmp;
                sort(maximum_bound.begin(), maximum_bound.end(), greator);
                bound = maximum_bound[3];
            }
        }
    }
    
    maximum_bound[3] += (maximum_bound[0] + maximum_bound[1] + maximum_bound[2]);
    maximum_bound[2] += (maximum_bound[0] + maximum_bound[1]);
    maximum_bound[1] += maximum_bound[0];
    
    // 어느 방향으로 갈 수 있다. 하지만 벽이나 자기자신은 불가
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < m ; j++) {
            dfs(1, 0, pair<int, int>(i, j), pair<int, int>(n, m));
        }
    }
    
    cout << (double)(clock() - start)/1000000 << "micro second\n"; 
    cout << "answer: ";
    cout << g_max;

    return 0;
}
