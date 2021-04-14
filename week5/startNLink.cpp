#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 둘다 정렬되어 있음
vector<int> get_difference(vector<int> total, vector<int> v) {
    vector<int> v2(v.size());
    for(size_t i = 0 ; i < v.size() ; i++) {
        auto it = find(total.begin(), total.end(), v[i]);
        total[it - total.begin()] = 0;
    }
    sort(total.begin(), total.end());
    for(size_t i = 0 ; i < v2.size() ; i++) {
        v2[i] = total[v.size()+i];
    }
    
    return v2;
}

int main(int argc, char** argv) {
    int n, min_diff = 1000000000;
    vector<vector<int>> stats;
    
    cin >> n;
    stats = vector<vector<int>>(n+1, vector<int>(n+1, 0));
    for(int i = 1 ; i <= n ; i++) 
        for(int j = 1 ; j <= n ; j++) 
            cin >> stats[i][j];
    
    vector<bool> code(n, 0);
    for(int i = n/2 ; i < n ; i++) code[i] = 1;
    do {
        vector<int> t1, t2;
        int tmp = 0, tmp2 = 0, cur_diff;
        for(int i = 0 ; i < n ; i++) {
            if(code[i]) t1.push_back(i+1);
            else t2.push_back(i+1);
        }
        
        for(int i = 0 ; i < n/2 ; i++) {
            for(int j = 0 ; j < n/2 ; j++) {
                if(i == j) continue;
                tmp  += stats[t1[i]][t1[j]];
                tmp2 += stats[t2[i]][t2[j]];
            }
        }
        cur_diff = (tmp - tmp2 > 0) ? tmp - tmp2 : tmp2 - tmp; 
        if(min_diff > cur_diff) min_diff = cur_diff;
    } while(std::next_permutation(code.begin(), code.end()));
    
    cout << min_diff;
    
    return 0;
}
