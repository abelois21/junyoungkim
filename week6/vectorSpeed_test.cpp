#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    const int n = 450;
    const int m = 550;
    int nums[n][m];
    int tmp = 0;
    vector<vector<int>> vnums(n, vector<int>(m, 0));
    for(int i = 0 ; i < n ; i++) {
	for(int j = 0 ; j < m ; j++) {
	    nums[i][j]  = i+j;
	    vnums[i][j] = i+j;
	}
    }

    clock_t start = clock();
    for(int i = 0 ; i < n ; i++) {
	for(int j = 0 ; j < m ; j++) {
	    tmp += nums[i][j];
	}
    }
    cout << (double)(clock() - start) << "us" << endl;

    start = clock();
    for(int i = 0 ; i < n ; i++) {
	for(int j = 0 ; j < m ; j++) {
	    tmp += vnums[i][j];
	}
    }
    cout << (double)(clock() - start) << "us" << endl;

    start = clock();
    for(auto i : vnums) {
	for(auto j : i) {
	    tmp += j;
	}
    }
    cout << (double)(clock() - start) << "us" << endl;

    start = clock();
    for(auto& i : vnums) {
	for(auto& j : i) {
	    tmp += j;
	}
    }
    cout << (double)(clock() - start) << "us" << endl;

    return 0;
}
