#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, int> mm;
vector<vector<char>> board;
int min_trial;
int n, m;

string loc2string(int* rb, int cnt) {
    string tmp;
    for(int i = 0 ; i < cnt ; i++) {
	tmp += to_string(*(rb+i));
    }
    return tmp;
}

// problem ? vector's size(row <-> col) change
void rotateQutuarCW(int* rb) {
    vector<vector<char>> tmp;
    int tmp2;

    for(int i = 0 ; i < n ; i++) {
	for(int j = 0 ; j < m ; j++) {
	    tmp[i][j] = board[i][j];
	}
    }

    for(int i = 0 ; i < n ; i++) {
	for(int j = 0 ; j < m ; j++) {
	    board[i][j] = tmp[j][n-i];
	}
    }

    tmp2 = *rb;
    *rb = *(rb+1);
    *(rb+1) = n-tmp2;

    tmp2 = *(rb+2);
    *(rb+2) = *(rb+3);
    *(rb+3) = n-tmp2;

    return;
}

int move_board(int* rb, int d) {
    int rotate_cnt, row_max, rst = 0;
    int R_col, B_col, R_row, B_row, cnt = 0;
    bool hole = 0;

    switch(d) {
	case 0:	// up
	    row_max = board.size();
	    rotate_cnt = 0;
	    break;
	case 1:	// righ
	    row_max = board[0].size();
	    rotateQutuarCW(rb); rotateQutuarCW(rb); rotateQutuarCW(rb);
	    rotate_cnt = 1;
	    break;
	case 2:	// down
	    row_max = board.size();
	    rotateQutuarCW(rb); rotateQutuarCW(rb);
	    rotate_cnt = 2;
	    break;
	case 3:	// left
	    row_max = board[0].size();
	    rotateQutuarCW(rb);
	    rotate_cnt = 3;
	    break;
    }

    // up
    R_row = *(rb);
    R_col = *(rb+1);
    B_row = *(rb+2);
    B_col = *(rb+3);
    if(R_col == B_col) {	// if R's col posiition is equal to B's
	for(int i = 0 ; i < row_max ; i++) {
	    switch(board[i][R_col]) {
		case '#':
		    cnt  = 0;
		    hole = 0;
		    break;
		case '.':
		    cnt += 1;
		    break;
		case 'O':
		    hole = 1;
		    break;
		case 'R':
		    if(hole) rst = 1;
		    R_row -= cnt;
		    cnt -= 1;
		    break;
		case 'B':
		    if(hole) rst = -1;
		    B_row -= cnt;
		    cnt -= 1;
		    break;
	    }
	    if(rst < 0) break;	// it's over
	}
    } else {
	for(int i = 0 ; i < row_max ; i++) {
	    switch(board[i][R_col]) {
		case '#':
		    cnt  = 0;
		    hole = 0;
		    break;
		case '.':
		    cnt += 1;
		    break;
		case 'O':
		    hole = 1;
		    break;
		case 'R':
		    if(hole) rst = 1;
		    R_row -= cnt;
		    break;
	    }
	    if(rst > 0) break;
	}

	cnt = 0;
	hole = 0;
	for(int i = 0 ; i < row_max ; i++) {
	    switch(board[i][B_col]) {
		case '#':
		    cnt  = 0;
		    hole = 0;
		    break;
		case '.':
		    cnt += 1;
		    break;
		case 'O':
		    hole = 1;
		    break;
		case 'B':
		    if(hole) rst = -1;
		    B_row -= cnt;
		    break;
	    }
	    if(rst < 0) break;
	}
    }
    *(rb)   = R_row;
    *(rb+1) = R_col;
    *(rb+2) = B_col;
    *(rb+3) = B_col;

    for(int i = 0 ; i < rotate_cnt; i++) rotateQutuarCW(rb);	// back up

    return rst;
}

void dfs(int* rb, int c) {
    if(c == 11) return -1;
    string code = loc2string(rb, 4);

    if(mm[code] < c) return;		// is duplicated and lower case

    for(int i = 0 ; i < 4 ; i++) {
	if(move_board(rb, i) > 0) {	// RED arrive at hole
	    if(min_trial > c+1) min_trial = c+1; 
	}

	code = loc2string(rb, 4);
	mm[code] = c;
	
	dfs(rb, c+1);
    }

    return;
}

int main(int argc, char** argv) {
    int rb[4];
    char ch;
    min_trial = 20;

    cin >> n >> m;
    for(int i = 0 ; i < n ; i++)
    {
	for(int j = 0 ; j < m ; j++)
	{
	    cin >> ch;
	    board[i][j] = ch;
	    if(ch == 'R') {
		rb[0] = i;
		rb[1] = j;
	    }
	    else if(ch == 'B') {
		rb[2] = i;
		rb[3] = j;
	    }
	}
    }

    cout << dfs(rb, 0);

    return 0;
}
