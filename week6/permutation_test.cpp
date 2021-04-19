#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

int main(int argc, char** argv) {
    int cbn_code[15], tmp = 0;
    for(int i = 0 ; i < 15 ; i++) cbn_code[i] = 0;
    cbn_code[14] = 1; cbn_code[13] = 1; cbn_code[12] = 1;

    clock_t start = clock();
    do {
//	for(int i = 0 ; i < 15 ; i++) {
//	    tmp += cbn_code[i];
//	}
	tmp = 0;
    } while(next_permutation(cbn_code, cbn_code+sizeof(cbn_code)/sizeof(cbn_code[0])));

    cout << (double)(clock() - start) << "us" << endl;

    start = clock();
    for(int i = 0 ; i < 13 ; i++) {
	tmp += i;
	for(int j = i+1 ; j < 14 ; j++) {
	    tmp += j;
	    for(int k = j+1 ; k < 15 ; k++) {
		tmp += k;
		tmp -= k;
	    }
	    tmp -= j;
	}
	tmp -= i;
    }

    cout << (double)(clock() - start) << "us" << endl;
    return 0;
}
