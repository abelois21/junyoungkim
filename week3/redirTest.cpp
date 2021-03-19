#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    int n, m;
    char c;

    cin >> n >> m;
    for(int i = 0 ; i < n ; i++) {
	for(int j = 0 ; j < m ; j++) {
	    cin >> c;
	    cout << c;
	}
	cout << endl;
    }

    return 0;
}
