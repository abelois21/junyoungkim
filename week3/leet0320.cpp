#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    int room, key;
    queue<int> waits;
    unordered_map<int, bool> um;

    waits.push(0);
    um[0] = 1;
    while(!waits.empty()) {
	room = waits.front();
	waits.pop();

	for(int i = 0 ; i < (int)rooms[room].size(); i++) {
	    key = rooms[room][i];
	    if(um[key]) {
		continue;
	    }
	    else {
		waits.push(key);
		um[key] = 1;
	    }
	}
    }

    if(rooms.size() == um.size()) {
	return 1;
    }
    else {
	return 0;
    }
}

int main(int argc, char** argv) {
    vector<vector<int>> rooms;
    vector<int> v;
    v.push_back(1);
    rooms.push_back(v);
    v.pop_back();
    v.push_back(2);
    rooms.push_back(v);
    v.pop_back();
    v.push_back(3);
    rooms.push_back(v);
    v.pop_back();
    rooms.push_back(v);
    cout << canVisitAllRooms(rooms);
    return 0;
}
