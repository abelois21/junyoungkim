#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;

class Solution {
public:
    bool isPossible(vector<int>& target) {
        priority_queue<int> pq;
        unsigned int sum = 0;
        for (int num : target)
            sum += num, pq.push(num);
        while (pq.top() != 1) {
            int num = pq.top();
            pq.pop();
            sum -= num;
            if (num <= sum || sum < 1) return false;
            num %= sum, sum += num, pq.push(num);
        }
        return true;
    }
};

int main(int argc, char** argv) {
    int n;
    clock_t start;
    vector<int> v;

    cin >> n;
    v = vector<int>(n, 0);
    for(int i = 0 ; i < n ; i++) cin >> v[n];

    Solution s;
    start = clock();
    cout << s.isPossible(v) << endl;
    cout << (double)(clock() - start) << "micro second\n";

    return 0;
}
