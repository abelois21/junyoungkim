#include <queue>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Solution1 {
public:
    bool isPossible(vector<int>& target) {
        int N = target.size(), cur_sum = 0, cur_most, temp;
        priority_queue<int> next;
        
        for(int i : target) {
            if((i - 1) % (N - 1) != 0) return 0;
            cur_sum += i;
            next.push(i);
        }

        while(next.top() != 1) {
            cur_most = next.top();
            next.pop();
            
            temp = cur_sum - cur_most;
            if(temp > cur_most) return 0;   // added
            cur_most -= temp;
	    cur_sum  -= temp;
            if(cur_most < 1) return 0;  // 위의 줄과 같은 의미

/*	    
	    cur_sum -= cur_most;
	    if(cur_sum >= cur_most || cur_sum < N-1) return 0;
	    cur_most %= cur_sum;
	    cur_sum  += cur_most;
*/
            next.push(cur_most);
        }

        return 1;
    }
};

int main(int argc, char** argv) {
    int n;
    clock_t start;
    vector<int> v;

    cin >> n;
    v = vector<int>(n, 0);
    for(int i = 0 ; i < n ; i++) {
	cin >> v[n];
    }

    Solution1 s;
    start = clock();
    cout << s.isPossible(v) << endl;
    cout << (double)(clock() - start) << "micro second\n";

    return 0;
}
