#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT
} Dir_t;

void debug_print(const vector<vector<char>>* board, pair<int, int> r, pair<int, int> b, pair<int, int> h);
void move(const vector<vector<char>>* board, Dir_t dir, pair<int, int> r, pair<int, int> b, const pair<int, int> hole);
inline void next(int& i, int& j, Dir_t d);

int n, m;

// 동적 프로그래밍으로 어떤 값을 활용하는 것 보단
// 단순히 방문했던 것을 판단하는 것이 좋을듯

int main(int argc, char** argv){
    int tmp;
    pair<int, int> r, b, hole;
    
    cin >> n >> m;
    vector<vector<char>> board(n, vector<char>(m, '0'));
    
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < m ; j++) {
            cin >> board[i][j];
            switch(tmp) {
                case 'R':
                    r = pair<int, int>(i, j);
                    break;
                case 'B':
                    r = pair<int, int>(i, j);
                    break;
                case 'O':
                    r = pair<int, int>(i, j);
                    break;
            }
        }
    }

    int idc;
    while(1) {
	cin >> idc;
	if(idc > 3 || idc < 0) break;
	move(&board, (Dir_t)idc, r, b, hole); 
    }
    
//  cout << g_min;
    return 0;
}


void debug_print(const vector<vector<char>>* board, pair<int, int> r, pair<int, int> b, pair<int, int> h) {
    for(int i = 0 ; i < n ; i++) {
	for(int j = 0 ; j < m ; j++) {
	    if(j == r.second) 
		if(i == r.first) {
		    cout << "R ";
		    continue;
		}
	    
	    if(j == b.second)
		if(j == b.first) {
		    cout << "B ";
		    continue;
		}

	    if(j == h.second)
		if(j == h.first) {
		    cout << "O ";
		    continue;
		}

	    cout << (*board)[i][j] << " ";
	}
	cout << endl;
    }
}

inline void next(int& i, int& j, Dir_t d) {
    switch(d) {
	case UP:
	    i += 1;
	    break;
	case RIGHT:
	    j += 1;
	    break;
	case DOWN:
	    i -= 1;
	    break;
	case LEFT:
	    j -= 1;
	    break;
    }
}

void move(const vector<vector<char>>* board, Dir_t dir, 
	pair<int, int> r, pair<int, int> b, const pair<int, int> hole) {
    int row, col, ball = -1;
    pair<int, int>* t;

    

    switch(dir) {
        case UP:
            t = (r.first < b.first) ? &r : &b;
            col = t->second;
            for(int i = t->first ; i >= 0 ; i--) {
                if((*board)[i][col] == '#') {
                    t->first = i+1;
                    ball = i+1;
                    break;
                } 
                if((*board)[i][col] == 'O') {
                    t->first = i;
                    break;
                }
            }
                
            t = (r.first < b.first) ? &b : &r;
            col = t->second;
            for(int i = t->first ; i >= 0 ; i--) {
                if(i == ball) {
                    t->first = ball+1;
                    break;
                }
                if((*board)[i][col] == '#') {
                    t->first = i+1;
                    break;
                } 
                if((*board)[i][col] == 'O') {
                    t->first = i;
                    break;
                }
            }                                
            break;
        case RIGHT:
            t = (r.second > b.second) ? &r : &b;
            row = t->first;
            for(int j = t->second ; j < m ; j++) {
                if((*board)[row][j] == '#') {
                    t->second = j-1;
                    ball = j-1;
                    break;
                } 
                if((*board)[row][j] == 'O') {
                    t->second = j;
                    break;
                }
            }
                
            t = (r.second > b.second) ? &b : &r;
            row = t->first;
            for(int j = t->second ; j < m ; j++) {
                if(j == ball) {
                    t->second = ball-1;
                    break;
                }
                if((*board)[row][j] == '#') {
                    t->second = j-1;
                    ball = j-1;
                    break;
                } 
                if((*board)[row][j] == 'O') {
                    t->second = j;
                    break;
                }
            }                                
            break;
        case DOWN:
            t = (r.first > b.first) ? &r : &b;
            col = t->second;
            for(int i = t->first ; i < n ; i++) {
                if((*board)[i][col] == '#') {
                    t->first = i-1;
                    ball = i-1;
                    break;
                } 
                if((*board)[i][col] == 'O') {
                    t->first = i;
                    break;
                }
            }
                
            t = (r.first > b.first) ? &b : &r;
            col = t->second;
            for(int i = t->first ; i < n ; i++) {
                if(i == ball) {
                    t->first = ball-1;
                    break;
                }
                if((*board)[i][col] == '#') {
                    t->first = i-1;
                    break;
                } 
                if((*board)[i][col] == 'O') {
                    t->first = i;
                    break;
                }
            }                                
            break;
        case LEFT:
            t = (r.second < b.second) ? &r : &b;
            row = t->first;
            for(int j = t->second ; j >= 0 ; j--) {
                if((*board)[row][j] == '#') {
                    t->second = j+1;
                    ball = j+1;
                    break;
                } 
                if((*board)[row][j] == 'O') {
                    t->second = j;
                    break;
                }
            }
                
            t = (r.second < b.second) ? &b : &r;
            row = t->first;
            for(int j = t->second ; j >= 0 ; j--) {
                if(j == ball) {
                    t->second = ball+1;
                    break;
                }
                if((*board)[row][j] == '#') {
                    t->second = j+1;
                    ball = j+1;
                    break;
                } 
                if((*board)[row][j] == 'O') {
                    t->second = j;
                    break;
                }
            }     
            break;
    }  

    debug_print(board, r, b, hole);
}

