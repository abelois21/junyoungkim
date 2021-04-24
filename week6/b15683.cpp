#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> cctv_loc;
vector<int> cctv_type;
int g_area;

vector<vector<int>> added_mm(vector<vector<int>>& mm, vector<pair<int, int>>* v1, 
                             vector<pair<int, int>>* v2 = NULL, vector<pair<int, int>>* v3 = NULL,
                             vector<pair<int, int>>* v4 = NULL) {
    vector<vector<int>> cv(mm.begin(), mm.end());
/*
    for(const auto& e : *v1) 
            cv[e.first][e.second] = -1;
    
    if(v2 != NULL) {
        for(const auto& e : *v2) 
            cv[e.first][e.second] = -1;
        
        if(v3 != NULL) {
            for(const auto& e : *v3) 
                cv[e.first][e.second] = -1;
            
            if(v4 != NULL) {
                for(const auto& e : *v4) 
                    cv[e.first][e.second] = -1;
            }
        }
    }
*/    
    for(auto it = v1->begin() ; it != v1->end() ; it++) 
            cv[it->first][it->second] = -1;
    
    if(v2 != NULL) {
        for(auto it = v2->begin() ; it != v2->end() ; it++) 
            cv[it->first][it->second] = -1;
        
        if(v3 != NULL) {
            for(auto it = v3->begin() ; it != v3->end() ; it++) 
                cv[it->first][it->second] = -1;
            
            if(v4 != NULL) {
                for(auto it = v4->begin() ; it != v4->end() ; it++) 
                    cv[it->first][it->second] = -1;
            }
        }
    }
    
    return cv;
}

void dfs(vector<vector<int>> mm, size_t order) {
    // 동적할당인데 이걸 배열로 선언하면 되나? 
    vector<pair<int, int>> added1, added2, added3, added4;
    int row = cctv_loc[order].first, col = cctv_loc[order].second;
    
    // added 벡터 설정
    for(int i = row-1 ; i >= 0 ; i--) {
        if(mm[i][col] == 6) break;
        added1.push_back(pair<int, int>(i, col));
    }
    for(int i = col-1 ; i >= 0 ; i--) {
        if(mm[row][i] == 6) break;
        added2.push_back(pair<int, int>(row, i));
    }
    for(size_t i = row+1 ; i < mm.size() ; i++) {
        if(mm[i][col] == 6) break;
        added3.push_back(pair<int, int>(i, col));
    }
    for(size_t i = col+1 ; i < mm[0].size() ; i++) {
        if(mm[row][i] == 6) break;
        added4.push_back(pair<int, int>(row, i));
    }
    
    // 마지막 cctv일 때, 사각지대 갱신
    if(order == cctv_type.size()) {
        int cur_area = 0; 
        for(const auto& i : mm) 
            for(const auto& j : i)
                if(j == 0) cur_area += 1;
        if(cur_area < g_area) g_area = cur_area;
        return;
    }
    
    switch(cctv_type[order]){
        case 1:
            dfs(added_mm(mm, &added1), order+1);
            dfs(added_mm(mm, &added2), order+1);
            dfs(added_mm(mm, &added3), order+1);
            dfs(added_mm(mm, &added4), order+1);
            break;
        case 2:
            dfs(added_mm(mm, &added1, &added3), order+1);
            dfs(added_mm(mm, &added2, &added4), order+1);
            break;
        case 3:
            dfs(added_mm(mm, &added1, &added2), order+1);
            dfs(added_mm(mm, &added2, &added3), order+1);
            dfs(added_mm(mm, &added3, &added4), order+1);
            dfs(added_mm(mm, &added4, &added1), order+1);
            break;
        case 4:
            dfs(added_mm(mm, &added1, &added2, &added3), order+1);
            dfs(added_mm(mm, &added2, &added3, &added4), order+1);
            dfs(added_mm(mm, &added3, &added4, &added1), order+1);
            dfs(added_mm(mm, &added4, &added1, &added2), order+1);
            break;
        case 5:
            dfs(added_mm(mm, &added1, &added2, &added3, &added4), order+1);
            break;
    }
    
    return;
}

int main(int argc, char** argv) {
    int n, m, tmp;
    vector<vector<int>> room;
    
    cin >> n >> m;
    g_area = n * m;
    room = vector<vector<int>>(n, vector<int>(m, 0));
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < m ; j++) { 
            cin >> tmp;
            room[i][j] = tmp;
            if(tmp == 0) continue;
            if(tmp != 6) {
                cctv_loc.push_back(pair<int, int>(i, j));
                cctv_type.push_back(tmp);
            }
        }
    }

    if(cctv_loc.size() == 0) {
	tmp = 0;
	for(int i = 0 ; i < n ; i++)
	    for(int j = 0 ; j < m ; j++)
		if(room[i][j] == 0) tmp += 1;
	g_area = tmp;
    } else {
        dfs(room, 0);
    }
    
    cout << g_area << endl;
    
    return 0;
}
