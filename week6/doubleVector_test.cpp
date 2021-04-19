#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

int main(int argc, char** argv) {
    vector<vector<int>> v(20, vector<int>(20, 0));
    vector<vector<int>> copy_v;
    for(size_t i = 0 ; i < 20 ; i++) {
	for(size_t j = 0 ; j < 20 ; j++) {
	    v[i][j] = i+j;
	}
    }

    copy_v = vector<vector<int>>(v.begin(), v.end());
    for(auto i : copy_v) {
	for(auto j : i) {
	    cout << j << " ";
	}
	cout << endl;
    }

    return 0;
}
