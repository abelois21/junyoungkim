#include <iostream>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void set_difference(const vector<int> v, vector<int>& v2, int n) {
    uint32_t code = -1;
    for(int i = 0 ; i < n/2 ; i++) {
	code = code ^ (1 << v[i]);
    }
    for(int i = 0 ; i < n ; i++) {
	if(code & 1 << i) v2[i] = i;
    }

    return;
}


bool m_permutation(int* arr, int n) {
    int value, change_idx;
	 
    // the arr is ascending from last
    // arr from change_idx+1 to last seem to be descending
    for(int i = n-1 ; i > 0 ; i--) {
	if(arr[i-1] < arr[i]) {
	    change_idx = i-1;
	    value = arr[change_idx];
	    cout << "change_idx: " << change_idx << " value: " << value << endl;	

	    if(i == n-1) {
		std::swap(arr[n-1], arr[n-2]);
		return 1;
	    }
	    break;
	}
	if(i == 1) {	// it was last permutation
	    std::sort(arr, arr+n);
	    return 0;
	}
    }

    int* ptr = std::upper_bound(arr+change_idx, arr+n, value);
    ptr -= 1;
    cout << "value : " << value << " *ptr: " << *ptr << endl;
    std::swap(arr[change_idx], *ptr);

    // after swaping, it still descendinng from change_idx+1 to last arr
    for(int i = 1 ; i <= (n-1-change_idx)/2 ; i++) 
	std::swap(arr[change_idx + i], arr[n - i]);
    
    return 1;
}

int main(int argc, char** argv) {
    int arr[] = { 1, 2, 3, 4, 5 };
    int arr2[] = { 1, 2, 5, 4, 3, 2, 5 };

    int* ptr = std::lower_bound(arr2, arr2+6, 3);
    cout << *ptr <<  " , " << (ptr - arr2) << endl;

    std::swap(arr2[5], *ptr);
    cout << arr2[0] << arr2[1] << arr2[2] << arr2[3] << arr2[4] << arr2[5] << arr2[6] << endl;

    cout << (int)(sizeof(arr)) << endl;
    do {
	cout << arr[0] << " , " << arr[1] << " , " << arr[2] << " , " << arr[3] << " , " << arr[4] << endl;
    } while(m_permutation(arr, sizeof(arr)/sizeof(arr[0])));

    return 0;
}
