#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

inline int combination(int n, int c) {
    if(c == 2) {
	return n * (n-1) / 2;
    }
    else if(c == 3) {
	return n * (n-1) * (n-2) / 6;
    }
    else {
	return -1;
    }
}

int threeSumMulti(vector<int>& arr, int target) {
    int n, tmp = -1, rst = 0;
    unordered_map<int, int> repeated;
    sort(arr.begin(), arr.end());

    for(int i = 0 ; i < arr.size() ; i++) {
	if(tmp < arr[i]) {
	    repeated[tmp] = n;
	    n = 1;
	    tmp = arr[i];
	}
	else {
	    n++;
	}
    }
    repeated[tmp] = n;

    int i = 0, j, k;
    bool flag = 0;
    while(i < arr.size()-2) {
	int a = arr[i], b, c;
	if(a * 3 > target) break;
	j = i+1;
	while(j < arr.size()-1) {
	    b = arr[j];
	    if(a + b * 2 > target) break;
	    k = j+1;
	    while(k < arr.size()) {
		c = arr[k];
		n = repeated[c];
		if(a + b + c > target) break;
		if(a + b + c == target) flag = 1;

		if(a == c) {
		    if(flag) rst += combination(repeated[c], 3);
		    k += (n-2);
		}
		else if(a == b) {
		    if(flag) rst += (combination(repeated[b], 2) * repeated[c]);
		    k += n;
		}
		else if(b == c) {
		    if(flag) rst += (combination(repeated[c], 2) * repeated[a]);
		    k += (n-1);
		}
	        else {
	    	    if(flag) rst += repeated[a] * repeated[b] * repeated[c];
	            k += n;
	        }
		flag = 0;
	    }
	    if(a == b) {
		j += (repeated[b]-1);
		continue;
	    }
	    else {
	    	j += repeated[b];
	    }
	}
	i += repeated[a];
    }

    return rst;
}

int threeSumMulti2(vector<int>& arr, int target) {
    int rst = 0;

    for(int i = 0 ; i < arr.size()-2 ; i++) {
	int a = arr[i], b, c;
	for(int j = i+1 ; j < arr.size()-1 ; j++) {
	    b = arr[j];
	    for(int k = j+1 ; k < arr.size() ; k++) {
		c = arr[k];
		if(a+b+c > target) break;
		if(a+b+c == target) {
		    rst += 1;
		}
	    }
	}
    }

    return rst;
}

int main(int argc, char** argv) {
    vector<int> arr;
    int n, tmp, target;
    clock_t start;
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> n;
    for(int i = 0 ; i < n ; i++) {
	cin >> tmp;
	arr.push_back(tmp);
    }
    cin >> target;

    start = clock();
    cout << threeSumMulti(arr, target) << endl;
    cout << "총 " << (double)(clock() - start)/1000000 << "마이크로초 소모\n";

    cout << endl;
    cout << "combination을 적용하지 않았을 때\n";
    start = clock();
    cout << threeSumMulti2(arr, target) << endl;
    cout << "총 " << (double)(clock() - start)/1000000 << "마이크로초 소모\n";

    vector<int> arr2 = vector<int>(1000, 0);
    target = 0;
    cout << endl << endl;

    start = clock();
    cout << threeSumMulti(arr2, target) << endl;
    cout << "총 " << (double)(clock() - start)/1000000 << "마이크로초 소모\n";

    cout << endl;
    cout << "combination을 적용하지 않았을 때\n";
    start = clock();
    cout << threeSumMulti2(arr2, target) << endl;
    cout << "총 " << (double)(clock() - start)/1000000 << "마이크로초 소모\n";

    return 0;
}
