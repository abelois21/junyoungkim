#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char** argv) {
//    int* cbn_code = new int(6);
    int cbn_code[6];
    for(int i = 0 ; i < 6 ; i++) cbn_code[i] = 0;
    cbn_code[5] = 1; cbn_code[4] = 1;

    do {
	cout << cbn_code[0] << " " << cbn_code[1] << " " << cbn_code[2] << " " << cbn_code[3] << " " 
	    << cbn_code[4] << " " << cbn_code[5] << endl;
    } while(next_permutation(cbn_code, cbn_code+sizeof(cbn_code)/sizeof(cbn_code[0])));
    return 0;
}
