#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <time.h>
using namespace std;

bool cmp(const vector<int> v1, const vector<int> v2) {
    if(v1[0] == v2[0]) {
        return v1[1] > v2[1];
    } else {
        return v1[0] > v2[0];    
    }
}

class Solution {
    unordered_map<int, int> um;
    unordered_map<int, int> potential_minimum;
    int max;
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if(envelopes.size() == 0) return 0;
        
        int tmp, c = 0;
        vector<pair<int, int>> t_v;
        max = 1;
        
        sort(envelopes.begin(), envelopes.end(), cmp);
        
        tmp = envelopes[0][0];
        for(int i = 1 ; i < envelopes.size() ; i++) {
            if(tmp != envelopes[i][0]) {
                t_v.push_back(pair<int, int>(c, i));
                tmp = envelopes[i][0];
                c += 1;
            }
        }
        
        for(int i = 0 ; i < t_v.size() ; i++) {
            potential_minimum[c - t_v[i].first] = t_v[i].second;
        }
        
        
        for(int i = 0 ; i < envelopes.size() ; i++) {
            if(um[i] != 0) continue;
            
            tmp = dfs(envelopes, i, 0);
            if(tmp > max) {
                max = tmp;
            }
            
            // advanced back-tracking , c >= max > 0
            if(max > 1 && potential_minimum[max-1] <= i) break;
        }
        
        um.clear();
        potential_minimum.clear();
        
        return max;
    }
    
    int dfs(const vector<vector<int>> v, int num, int value) {
        int tmp, bound, node_max = 1;
        
        bound = v.size();
        if((this->max - value - 1) > 1) {   // advanced back-tracking
            bound = potential_minimum[this->max - value -1];    
        }
    
        for(int i = num+1 ; i < bound ; i++) {
            if(v[num][0] == v[i][0] || v[num][1] <= v[i][1]) { // in don't meet condition
                continue;    
            }
            
            if(um[i] != 0) {
                if(node_max <= um[i] + 1) {
                    node_max = um[i] + 1;
                }
            }
            else {
                tmp = dfs(v, i, value+1) + 1;
                if(node_max < tmp) {
                    node_max = tmp;
                }
            }
        }
        
        um[num] = node_max;
        return node_max;
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
