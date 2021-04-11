#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <time.h>
using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& E) {
        sort(E.begin(), E.end(), [](vector<int>& a, vector<int>& b) 
             -> bool {return a[0] == b[0] ? b[1] < a[1] : a[0] < b[0];});
        vector<int> dp;
        for (auto& env : E) {
            int height = env[1];
            int left = lower_bound(dp.begin(), dp.end(), height) - dp.begin();
            if (left == dp.size()) dp.push_back(height);
            dp[left] = height;
        }
        return dp.size();
    }
};

int main(int argc, char** argv) {
    int num, a, b;
    vector<vector<int>> envelopes;
    vector<int> t_v;
    clock_t start;

    while(1) {
	scanf("[%d,%d],", &a, &b);
	if(a == -1 && b == -1) break;
	t_v.push_back(a); t_v.push_back(b);
	envelopes.push_back(t_v);
	t_v.clear();
    }

    start = clock();

    Solution s;
    cout << s.maxEnvelopes(envelopes) << endl;
    cout << "time record: " << (double)(clock() - start)/1000000 << "micro seconds\n";

    return 0;
}
